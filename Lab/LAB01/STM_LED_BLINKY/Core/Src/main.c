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
#define SEGMENT_PINS  (SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | \
                       SEG_E_Pin | SEG_F_Pin | SEG_G_Pin)
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
void display7SEG(int num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* The physical display is common-cathode: SET = on, RESET = off. */
static void setSegments(GPIO_PinState a, GPIO_PinState b, GPIO_PinState c,
                        GPIO_PinState d, GPIO_PinState e, GPIO_PinState f,
                        GPIO_PinState g)
{
  HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, a);
  HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, b);
  HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, c);
  HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, d);
  HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, e);
  HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, f);
  HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, g);
}

void display7SEG(int num)
{
  /* Each call lists the states of A, B, C, D, E, F and G in that order. */
  switch (num)
  {
    case 0:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
      break;
    case 1:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 2:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET);
      break;
    case 3:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
      break;
    case 4:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 5:
      setSegments(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 6:
      setSegments(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 7:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 8:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 9:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    default:
      HAL_GPIO_WritePin(GPIOA, SEGMENT_PINS, GPIO_PIN_RESET);
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
  int counter = 0;

  /* Startup hardware test: all seven segments on for two seconds. */
  HAL_GPIO_WritePin(GPIOA, SEGMENT_PINS, GPIO_PIN_SET);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(GPIOA, SEGMENT_PINS, GPIO_PIN_RESET);
  HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if (counter >= 10)
    {
      counter = 0;
    }

    display7SEG(counter++);
    HAL_Delay(1000);
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEGMENT_PINS, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 PA8 PA9 PA10 */
  GPIO_InitStruct.Pin = SEGMENT_PINS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
