#include "main.h"
#include "traffic_led.h"

/* Direction bits: N=0, E=1, S=2, W=3. Opposite directions share a wire. */
static uint16_t pins_for(TrafficColour colour, uint8_t direction_mask)
{
  uint16_t pins = 0U;
  if ((direction_mask & 0x0AU) != 0U)
  {
    pins |= colour == TRAFFIC_RED ? RED_H_Pin :
            colour == TRAFFIC_AMBER ? YEL_H_Pin : GRN_H_Pin;
  }
  if ((direction_mask & 0x05U) != 0U)
  {
    pins |= colour == TRAFFIC_RED ? RED_V_Pin :
            colour == TRAFFIC_AMBER ? YEL_V_Pin : GRN_V_Pin;
  }
  return pins;
}

void traffic_led_init(void)
{
  traffic_led_all_off();
}

void traffic_led_all_off(void)
{
  HAL_GPIO_WritePin(GPIOA, TRAFFIC_LED_ALL_Pin, GPIO_PIN_SET);
}

void traffic_led_set_mask(TrafficColour colour, uint8_t direction_mask)
{
  uint16_t pins;
  if (colour >= TRAFFIC_COLOUR_COUNT) return;
  pins = pins_for(colour, direction_mask);
  if (pins != 0U) HAL_GPIO_WritePin(GPIOA, pins, GPIO_PIN_RESET);
}

void traffic_led_set_masks(uint8_t red_mask, uint8_t amber_mask,
                           uint8_t green_mask)
{
  traffic_led_all_off();
  traffic_led_set_mask(TRAFFIC_RED, red_mask);
  traffic_led_set_mask(TRAFFIC_AMBER, amber_mask);
  traffic_led_set_mask(TRAFFIC_GREEN, green_mask);
}
