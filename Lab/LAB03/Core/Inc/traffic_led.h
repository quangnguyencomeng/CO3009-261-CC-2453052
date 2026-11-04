#ifndef TRAFFIC_LED_H
#define TRAFFIC_LED_H

#include <stdint.h>

typedef enum
{
  TRAFFIC_RED = 0,
  TRAFFIC_AMBER,
  TRAFFIC_GREEN,
  TRAFFIC_COLOUR_COUNT
} TrafficColour;

void traffic_led_init(void);
void traffic_led_all_off(void);
void traffic_led_set_mask(TrafficColour colour, uint8_t direction_mask);
void traffic_led_set_masks(uint8_t red_mask, uint8_t amber_mask,
                           uint8_t green_mask);

#endif /* TRAFFIC_LED_H */
