#include "traffic_app.h"
#include "app_config.h"
#include "button.h"
#include "seven_segment.h"
#include "soft_timer.h"
#include "traffic_led.h"

#define VERTICAL_MASK   0x05U
#define HORIZONTAL_MASK 0x0AU

typedef enum { MODE_NORMAL = 1, MODE_RED, MODE_AMBER, MODE_GREEN } AppMode;
typedef enum { H_GREEN = 0, H_AMBER, V_GREEN, V_AMBER } TrafficPhase;

static AppMode mode;
static TrafficPhase phase;
static uint8_t durations[TRAFFIC_COLOUR_COUNT];
static uint8_t remaining;
static uint8_t blink_on;
static SoftTimer second_timer;
static SoftTimer blink_timer;

/* One road is red for the whole green+amber interval of the other road. */
static void reconcile_durations(TrafficColour changed)
{
  uint8_t red = durations[TRAFFIC_RED];
  uint8_t amber = durations[TRAFFIC_AMBER];
  uint8_t green = durations[TRAFFIC_GREEN];
  if (changed == TRAFFIC_RED)
  {
    if (red > amber) durations[TRAFFIC_GREEN] = red - amber;
    else durations[TRAFFIC_RED] = amber + green <= 99U ? amber + green : 99U;
  }
  else if (changed == TRAFFIC_AMBER)
  {
    if (amber >= red)
    {
      amber = TRAFFIC_MIN_DURATION_SECONDS;
      durations[TRAFFIC_AMBER] = amber;
    }
    durations[TRAFFIC_GREEN] = red - amber;
  }
  else
  {
    durations[TRAFFIC_RED] = green + amber <= 99U ? green + amber : 99U;
  }
}

static void set_pair(uint8_t horizontal, uint8_t vertical)
{
  if (horizontal > 99U) horizontal = 99U;
  if (vertical > 99U) vertical = 99U;
  seven_segment_set_values((int8_t)(horizontal / 10U), (int8_t)(horizontal % 10U),
                           (int8_t)(vertical / 10U), (int8_t)(vertical % 10U));
}

static void render_normal(void)
{
  uint8_t amber = durations[TRAFFIC_AMBER];
  switch (phase)
  {
    case H_GREEN:
      traffic_led_set_masks(VERTICAL_MASK, 0U, HORIZONTAL_MASK);
      set_pair((uint8_t)(remaining + amber), remaining);
      break;
    case H_AMBER:
      traffic_led_set_masks(VERTICAL_MASK, HORIZONTAL_MASK, 0U);
      set_pair(remaining, remaining);
      break;
    case V_GREEN:
      traffic_led_set_masks(HORIZONTAL_MASK, 0U, VERTICAL_MASK);
      set_pair(remaining, (uint8_t)(remaining + amber));
      break;
    default:
      traffic_led_set_masks(HORIZONTAL_MASK, VERTICAL_MASK, 0U);
      set_pair(remaining, remaining);
      break;
  }
}

static TrafficColour edited_colour(void)
{
  return mode == MODE_RED ? TRAFFIC_RED :
         mode == MODE_AMBER ? TRAFFIC_AMBER : TRAFFIC_GREEN;
}

static void render_edit(void)
{
  TrafficColour colour = edited_colour();
  uint8_t value = durations[colour];
  traffic_led_all_off();
  if (blink_on != 0U) traffic_led_set_mask(colour, 0x0FU);
  seven_segment_set_values((int8_t)(value / 10U), (int8_t)(value % 10U),
                           0, (int8_t)mode);
}

static void enter_normal(void)
{
  mode = MODE_NORMAL;
  phase = H_GREEN;
  remaining = durations[TRAFFIC_GREEN];
  soft_timer_start(&second_timer, 1000U);
  soft_timer_cancel(&blink_timer);
  render_normal();
}

static void enter_edit(AppMode next_mode)
{
  mode = next_mode;
  blink_on = 1U;
  soft_timer_start(&blink_timer, LAB3_BLINK_HALF_PERIOD_MS);
  render_edit();
}

void traffic_app_init(void)
{
  durations[TRAFFIC_RED] = DEFAULT_RED_DURATION_SECONDS;
  durations[TRAFFIC_AMBER] = DEFAULT_AMBER_DURATION_SECONDS;
  durations[TRAFFIC_GREEN] = DEFAULT_GREEN_DURATION_SECONDS;
  button_init();
  seven_segment_init();
  traffic_led_init();
  enter_normal();
}

void traffic_app_timer_tick(void)
{
  button_tick();
  seven_segment_scan_tick();
  soft_timer_tick(&second_timer);
  soft_timer_tick(&blink_timer);
}

void traffic_app_run(void)
{
  uint8_t increase_pressed = button_take_press(BUTTON_INCREASE);
  uint8_t set_pressed = button_take_press(BUTTON_SET);
  if (button_take_press(BUTTON_MODE) != 0U)
  {
    if (mode == MODE_NORMAL) enter_edit(MODE_RED);
    else if (mode == MODE_RED) enter_edit(MODE_AMBER);
    else if (mode == MODE_AMBER) enter_edit(MODE_GREEN);
    else enter_normal();
    return;
  }

  if (mode != MODE_NORMAL)
  {
    if (increase_pressed != 0U)
    {
      TrafficColour colour = edited_colour();
      durations[colour]++;
      if (durations[colour] > TRAFFIC_MAX_DURATION_SECONDS)
        durations[colour] = TRAFFIC_MIN_DURATION_SECONDS;
      reconcile_durations(colour);
      render_edit();
    }
    if (set_pressed != 0U)
    {
      enter_normal();
      return;
    }
    if (soft_timer_take(&blink_timer) != 0U)
    {
      blink_on = blink_on == 0U ? 1U : 0U;
      soft_timer_start(&blink_timer, LAB3_BLINK_HALF_PERIOD_MS);
      render_edit();
    }
    return;
  }

  if (soft_timer_take(&second_timer) != 0U)
  {
    if (remaining > 1U) remaining--;
    else
    {
      phase = (TrafficPhase)(((uint8_t)phase + 1U) % 4U);
      remaining = (phase == H_AMBER || phase == V_AMBER) ?
                  durations[TRAFFIC_AMBER] : durations[TRAFFIC_GREEN];
    }
    soft_timer_start(&second_timer, 1000U);
    render_normal();
  }
}
