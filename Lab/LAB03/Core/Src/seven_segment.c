#include "main.h"
#include "seven_segment.h"

static volatile int8_t display_buffer[4] = {-1, -1, -1, -1};
static uint8_t scan_phase;
static const uint8_t digit_patterns[10] =
  {0x3FU, 0x06U, 0x5BU, 0x4FU, 0x66U, 0x6DU, 0x7DU, 0x07U, 0x7FU, 0x6FU};

static void write_bus(int8_t digit, uint8_t shift)
{
  uint8_t pattern = 0U;
  uint16_t bus = (uint16_t)(0x7FU << shift);
  if (digit >= 0 && digit <= 9) pattern = digit_patterns[(uint8_t)digit];
  HAL_GPIO_WritePin(GPIOB, bus, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, (uint16_t)pattern << shift, GPIO_PIN_RESET);
}

void seven_segment_init(void)
{
  scan_phase = 0U;
  HAL_GPIO_WritePin(GPIOA, DIGIT_ALL_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, SEG_H_ALL_Pin | SEG_V_ALL_Pin, GPIO_PIN_SET);
}

void seven_segment_set_values(int8_t digit0, int8_t digit1,
                              int8_t digit2, int8_t digit3)
{
  display_buffer[0] = digit0;
  display_buffer[1] = digit1;
  display_buffer[2] = digit2;
  display_buffer[3] = digit3;
}

void seven_segment_scan_tick(void)
{
  HAL_GPIO_WritePin(GPIOA, DIGIT_ALL_Pin, GPIO_PIN_SET);
  if (scan_phase == 0U)
  {
    write_bus(display_buffer[0], 0U);
    write_bus(display_buffer[2], 7U);
    HAL_GPIO_WritePin(GPIOA, DIGIT0_Pin | DIGIT2_Pin, GPIO_PIN_RESET);
    scan_phase = 1U;
  }
  else
  {
    write_bus(display_buffer[1], 0U);
    write_bus(display_buffer[3], 7U);
    HAL_GPIO_WritePin(GPIOA, DIGIT1_Pin | DIGIT3_Pin, GPIO_PIN_RESET);
    scan_phase = 0U;
  }
}
