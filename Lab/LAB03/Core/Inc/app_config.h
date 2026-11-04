#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/* Lab 3 is cumulative. The final integrated project is exercise 10. */
#define LAB3_DEMO_EXERCISE             10U

/* Exercise 4: choose 1U or 100U, then rebuild the firmware. */
#define LAB3_TIMER_TICK_MS              1U
#define LAB3_BUTTON_DEBOUNCE_SAMPLES  2U
#define LAB3_BLINK_HALF_PERIOD_MS     250U

#define TRAFFIC_DIRECTION_COUNT        4U
#define TRAFFIC_MIN_DURATION_SECONDS  1U
#define TRAFFIC_MAX_DURATION_SECONDS 99U
#define DEFAULT_RED_DURATION_SECONDS  10U
#define DEFAULT_AMBER_DURATION_SECONDS 3U
#define DEFAULT_GREEN_DURATION_SECONDS 7U

#endif /* APP_CONFIG_H */
