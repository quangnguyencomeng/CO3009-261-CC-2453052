#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

typedef enum
{
  BUTTON_MODE = 0,
  BUTTON_INCREASE,
  BUTTON_SET,
  BUTTON_COUNT
} ButtonId;

void button_init(void);
void button_tick(void);
uint8_t button_take_press(ButtonId id);
uint8_t button_is_down(ButtonId id);

#endif /* BUTTON_H */
