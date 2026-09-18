/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SEG1_A_Pin GPIO_PIN_0
#define SEG1_A_GPIO_Port GPIOA
#define SEG1_B_Pin GPIO_PIN_1
#define SEG1_B_GPIO_Port GPIOA
#define SEG1_C_Pin GPIO_PIN_2
#define SEG1_C_GPIO_Port GPIOA
#define SEG1_D_Pin GPIO_PIN_3
#define SEG1_D_GPIO_Port GPIOA
#define SEG1_E_Pin GPIO_PIN_4
#define SEG1_E_GPIO_Port GPIOA
#define SEG1_F_Pin GPIO_PIN_5
#define SEG1_F_GPIO_Port GPIOA
#define SEG1_G_Pin GPIO_PIN_6
#define SEG1_G_GPIO_Port GPIOA
#define SEG2_A_Pin GPIO_PIN_7
#define SEG2_A_GPIO_Port GPIOA
#define SEG2_B_Pin GPIO_PIN_8
#define SEG2_B_GPIO_Port GPIOA
#define SEG2_C_Pin GPIO_PIN_9
#define SEG2_C_GPIO_Port GPIOA
#define SEG2_D_Pin GPIO_PIN_10
#define SEG2_D_GPIO_Port GPIOA
#define SEG2_E_Pin GPIO_PIN_11
#define SEG2_E_GPIO_Port GPIOA
#define SEG2_F_Pin GPIO_PIN_12
#define SEG2_F_GPIO_Port GPIOA
#define SEG2_G_Pin GPIO_PIN_13
#define SEG2_G_GPIO_Port GPIOA

#define LG1_Pin GPIO_PIN_0
#define LG1_GPIO_Port GPIOB
#define LY1_Pin GPIO_PIN_1
#define LY1_GPIO_Port GPIOB
#define LR1_Pin GPIO_PIN_2
#define LR1_GPIO_Port GPIOB
#define LG2_Pin GPIO_PIN_3
#define LG2_GPIO_Port GPIOB
#define LY2_Pin GPIO_PIN_4
#define LY2_GPIO_Port GPIOB
#define LR2_Pin GPIO_PIN_5
#define LR2_GPIO_Port GPIOB
#define LG3_Pin GPIO_PIN_6
#define LG3_GPIO_Port GPIOB
#define LY3_Pin GPIO_PIN_7
#define LY3_GPIO_Port GPIOB
#define LR3_Pin GPIO_PIN_8
#define LR3_GPIO_Port GPIOB
#define LG4_Pin GPIO_PIN_9
#define LG4_GPIO_Port GPIOB
#define LY4_Pin GPIO_PIN_10
#define LY4_GPIO_Port GPIOB
#define LR4_Pin GPIO_PIN_11
#define LR4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
