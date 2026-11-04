#include "main.h"
#include "button.h"
#include "app_config.h"

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t pin;
  GPIO_PinState raw_state;
  GPIO_PinState stable_state;
  uint8_t stable_samples;
} ButtonState;

static ButtonState buttons[BUTTON_COUNT] =
{
  { BTN_MODE_GPIO_Port, BTN_MODE_Pin, GPIO_PIN_SET, GPIO_PIN_SET, 0U },
  { BTN_INCREASE_GPIO_Port, BTN_INCREASE_Pin, GPIO_PIN_SET, GPIO_PIN_SET, 0U },
  { BTN_SET_GPIO_Port, BTN_SET_Pin, GPIO_PIN_SET, GPIO_PIN_SET, 0U }
};

static volatile uint8_t press_events;

void button_init(void)
{
  uint32_t i;

  press_events = 0U;
  for (i = 0U; i < BUTTON_COUNT; i++)
  {
    buttons[i].raw_state = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);
    buttons[i].stable_state = buttons[i].raw_state;
    buttons[i].stable_samples = LAB3_BUTTON_DEBOUNCE_SAMPLES;
  }
}

void button_tick(void)
{
  uint32_t i;

  for (i = 0U; i < BUTTON_COUNT; i++)
  {
    GPIO_PinState sample = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

    if (sample == buttons[i].raw_state)
    {
      if (buttons[i].stable_samples < LAB3_BUTTON_DEBOUNCE_SAMPLES)
      {
        buttons[i].stable_samples++;
      }
    }
    else
    {
      buttons[i].raw_state = sample;
      buttons[i].stable_samples = 1U;
    }

    if (buttons[i].stable_samples >= LAB3_BUTTON_DEBOUNCE_SAMPLES &&
        buttons[i].stable_state != buttons[i].raw_state)
    {
      buttons[i].stable_state = buttons[i].raw_state;
      if (buttons[i].stable_state == GPIO_PIN_RESET)
      {
        press_events |= (uint8_t)(1U << i);
      }
    }
  }
}

uint8_t button_take_press(ButtonId id)
{
  uint8_t mask;

  if (id >= BUTTON_COUNT)
  {
    return 0U;
  }

  mask = (uint8_t)(1U << id);
  if ((press_events & mask) == 0U)
  {
    return 0U;
  }

  press_events &= (uint8_t)~mask;
  return 1U;
}

uint8_t button_is_down(ButtonId id)
{
  if (id >= BUTTON_COUNT)
  {
    return 0U;
  }

  return buttons[id].stable_state == GPIO_PIN_RESET ? 1U : 0U;
}
