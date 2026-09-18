/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEG1_PINS (SEG1_A_Pin | SEG1_B_Pin | SEG1_C_Pin | SEG1_D_Pin | \
                   SEG1_E_Pin | SEG1_F_Pin | SEG1_G_Pin)
#define SEG2_PINS (SEG2_A_Pin | SEG2_B_Pin | SEG2_C_Pin | SEG2_D_Pin | \
                   SEG2_E_Pin | SEG2_F_Pin | SEG2_G_Pin)
#define TRAFFIC_PINS (LG1_Pin | LY1_Pin | LR1_Pin | LG2_Pin | LY2_Pin | \
                      LR2_Pin | LG3_Pin | LY3_Pin | LR3_Pin | LG4_Pin | \
                      LY4_Pin | LR4_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(uint8_t display, int num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* Both displays are common-anode: RESET = segment on, SET = segment off. */
static void setSegments(uint8_t display, GPIO_PinState a, GPIO_PinState b,
                        GPIO_PinState c, GPIO_PinState d, GPIO_PinState e,
                        GPIO_PinState f, GPIO_PinState g)
{
  uint16_t pinA = (display == 1U) ? SEG1_A_Pin : SEG2_A_Pin;
  uint16_t pinB = (display == 1U) ? SEG1_B_Pin : SEG2_B_Pin;
  uint16_t pinC = (display == 1U) ? SEG1_C_Pin : SEG2_C_Pin;
  uint16_t pinD = (display == 1U) ? SEG1_D_Pin : SEG2_D_Pin;
  uint16_t pinE = (display == 1U) ? SEG1_E_Pin : SEG2_E_Pin;
  uint16_t pinF = (display == 1U) ? SEG1_F_Pin : SEG2_F_Pin;
  uint16_t pinG = (display == 1U) ? SEG1_G_Pin : SEG2_G_Pin;

  HAL_GPIO_WritePin(GPIOA, pinA, a);
  HAL_GPIO_WritePin(GPIOA, pinB, b);
  HAL_GPIO_WritePin(GPIOA, pinC, c);
  HAL_GPIO_WritePin(GPIOA, pinD, d);
  HAL_GPIO_WritePin(GPIOA, pinE, e);
  HAL_GPIO_WritePin(GPIOA, pinF, f);
  HAL_GPIO_WritePin(GPIOA, pinG, g);
}

/* All traffic-light cathodes are connected to GND: SET = LED on. */
static void setTraffic(GPIO_PinState lg1, GPIO_PinState ly1,
                       GPIO_PinState lr1, GPIO_PinState lg2,
                       GPIO_PinState ly2, GPIO_PinState lr2,
                       GPIO_PinState lg3, GPIO_PinState ly3,
                       GPIO_PinState lr3, GPIO_PinState lg4,
                       GPIO_PinState ly4, GPIO_PinState lr4)
{
  HAL_GPIO_WritePin(GPIOB, LG1_Pin, lg1);
  HAL_GPIO_WritePin(GPIOB, LY1_Pin, ly1);
  HAL_GPIO_WritePin(GPIOB, LR1_Pin, lr1);
  HAL_GPIO_WritePin(GPIOB, LG2_Pin, lg2);
  HAL_GPIO_WritePin(GPIOB, LY2_Pin, ly2);
  HAL_GPIO_WritePin(GPIOB, LR2_Pin, lr2);
  HAL_GPIO_WritePin(GPIOB, LG3_Pin, lg3);
  HAL_GPIO_WritePin(GPIOB, LY3_Pin, ly3);
  HAL_GPIO_WritePin(GPIOB, LR3_Pin, lr3);
  HAL_GPIO_WritePin(GPIOB, LG4_Pin, lg4);
  HAL_GPIO_WritePin(GPIOB, LY4_Pin, ly4);
  HAL_GPIO_WritePin(GPIOB, LR4_Pin, lr4);
}

void display7SEG(uint8_t display, int num)
{
  /* Each call lists A, B, C, D, E, F and G in that order. */
  switch (num)
  {
    case 0:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
      break;
    case 1:
      setSegments(display, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 2:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
      break;
    case 3:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
      break;
    case 4:
      setSegments(display, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 5:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 6:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 7:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 8:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 9:
      setSegments(display, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    default:
      setSegments(display, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /* Startup hardware test: both displays show all segments for two seconds. */
  HAL_GPIO_WritePin(GPIOA, SEG1_PINS | SEG2_PINS, GPIO_PIN_RESET);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(GPIOA, SEG1_PINS | SEG2_PINS, GPIO_PIN_SET);
  HAL_Delay(500);
  setTraffic(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
             GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
             GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
             GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Poles 1 and 2 are opposite; poles 3 and 4 are opposite.
       Red lasts 5 s = 3 s green + 2 s yellow. */
    for (int t = 5; t > 0; --t)
    {
      if (t > 2)
      {
        setTraffic(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                   GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
        display7SEG(1, t - 2);
      }
      else
      {
        setTraffic(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                   GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
        display7SEG(1, t);
      }
      display7SEG(2, t);
      HAL_Delay(1000);
    }

    for (int t = 5; t > 0; --t)
    {
      display7SEG(1, t);
      if (t > 2)
      {
        setTraffic(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                   GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
        display7SEG(2, t - 2);
      }
      else
      {
        setTraffic(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                   GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                   GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
        display7SEG(2, t);
      }
      HAL_Delay(1000);
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEG1_PINS | SEG2_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, TRAFFIC_PINS, GPIO_PIN_RESET);

  /* Configure PA0-PA13 for the two common-anode 7-segment displays. */
  GPIO_InitStruct.Pin = SEG1_PINS | SEG2_PINS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure PB0-PB11 for the four common-cathode traffic-light poles. */
  GPIO_InitStruct.Pin = TRAFFIC_PINS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
