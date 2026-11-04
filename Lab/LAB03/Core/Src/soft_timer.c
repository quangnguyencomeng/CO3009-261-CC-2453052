#include "soft_timer.h"
#include "app_config.h"

void soft_timer_start(SoftTimer *timer, uint32_t duration_ms)
{
  uint32_t ticks;

  if (timer == 0)
  {
    return;
  }

  ticks = (duration_ms + LAB3_TIMER_TICK_MS - 1U) / LAB3_TIMER_TICK_MS;
  if (ticks == 0U)
  {
    ticks = 1U;
  }

  timer->remaining_ticks = ticks;
  timer->expired = 0U;
}

void soft_timer_cancel(SoftTimer *timer)
{
  if (timer == 0)
  {
    return;
  }

  timer->remaining_ticks = 0U;
  timer->expired = 0U;
}

void soft_timer_tick(SoftTimer *timer)
{
  if (timer == 0 || timer->expired != 0U)
  {
    return;
  }

  if (timer->remaining_ticks > 0U)
  {
    timer->remaining_ticks--;
    if (timer->remaining_ticks == 0U)
    {
      timer->expired = 1U;
    }
  }
}

uint8_t soft_timer_take(SoftTimer *timer)
{
  uint8_t result;

  if (timer == 0)
  {
    return 0U;
  }

  result = timer->expired;
  timer->expired = 0U;
  return result;
}
