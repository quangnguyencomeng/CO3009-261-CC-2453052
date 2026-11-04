#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include <stdint.h>

typedef struct
{
  volatile uint32_t remaining_ticks;
  volatile uint8_t expired;
} SoftTimer;

void soft_timer_start(SoftTimer *timer, uint32_t duration_ms);
void soft_timer_cancel(SoftTimer *timer);
void soft_timer_tick(SoftTimer *timer);
uint8_t soft_timer_take(SoftTimer *timer);

#endif /* SOFT_TIMER_H */
