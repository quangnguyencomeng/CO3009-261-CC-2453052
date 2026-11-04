#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>

void seven_segment_init(void);
void seven_segment_set_values(int8_t digit0, int8_t digit1,
                              int8_t digit2, int8_t digit3);
void seven_segment_scan_tick(void);

#endif /* SEVEN_SEGMENT_H */
