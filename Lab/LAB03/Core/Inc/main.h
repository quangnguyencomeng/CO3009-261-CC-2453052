#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Error_Handler(void);

/* Six active-low light outputs on the working two-road circuit. */
#define RED_H_Pin              GPIO_PIN_1
#define GRN_H_Pin              GPIO_PIN_2
#define YEL_H_Pin              GPIO_PIN_3
#define RED_V_Pin              GPIO_PIN_4
#define YEL_V_Pin              GPIO_PIN_5
#define GRN_V_Pin              GPIO_PIN_6
#define TRAFFIC_LED_ALL_Pin    (RED_H_Pin | YEL_H_Pin | GRN_H_Pin | RED_V_Pin | YEL_V_Pin | GRN_V_Pin)

/* Four active-low PNP digit enables. */
#define DIGIT0_Pin             GPIO_PIN_7
#define DIGIT1_Pin             GPIO_PIN_8
#define DIGIT2_Pin             GPIO_PIN_9
#define DIGIT3_Pin             GPIO_PIN_10
#define DIGIT_ALL_Pin          (DIGIT0_Pin | DIGIT1_Pin | DIGIT2_Pin | DIGIT3_Pin)

/* Independent common-anode segment buses. */
#define SEG_H_ALL_Pin          ((uint16_t)0x007FU)
#define SEG_V_ALL_Pin          ((uint16_t)0x3F80U)

/* Active-low buttons with internal pull-ups. */
#define BTN_MODE_Pin           GPIO_PIN_11
#define BTN_MODE_GPIO_Port     GPIOA
#define BTN_INCREASE_Pin       GPIO_PIN_12
#define BTN_INCREASE_GPIO_Port GPIOA
#define BTN_SET_Pin            GPIO_PIN_13
#define BTN_SET_GPIO_Port      GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
