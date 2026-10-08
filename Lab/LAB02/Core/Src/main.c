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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;


/* USER CODE BEGIN PV */
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 5, 0, 8};

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
const uint32_t MATRIX_SHIFT_PERIOD_MS = 300U;
uint32_t matrix_last_shift_tick = 0U;

/* Each byte is the ROW0..ROW7 pattern for one scanned column.
   ROW = HIGH turns on the LED in the currently selected column.
   ENM0..ENM7 drive ULN2803; one column is selected at a time.

   Exercise 10 rotates the columns to move the letter to the left.
   Matrix scanning and animation use independent time scales.

       ........
       ........
       ...##...
       ..#..#..
       ..####..
       ..#..#..
       ........
       ........

   Column-wise data for the centered 4x4 character 'A'. */
uint8_t matrix_buffer[8] = {
    0x00, 0x00, 0x38, 0x14,
    0x14, 0x38, 0x00, 0x00
};

int hour = 15;
int minute = 8;
int second = 50;

void updateClockBuffer(void)
{
  led_buffer[0] = hour / 10;
  led_buffer[1] = hour % 10;
  led_buffer[2] = minute / 10;
  led_buffer[3] = minute % 10;
}

/* Software timers. TIM2 interrupt period = 1 ms. */
volatile int timer0_counter = 0;
volatile int timer0_flag = 0;

volatile int timer1_counter = 0;
volatile int timer1_flag = 0;

volatile int timer2_counter = 0;
volatile int timer2_flag = 0;

const int TIMER_CYCLE = 1;

void setTimer0(int duration)
{
  timer0_counter = duration / TIMER_CYCLE;
  timer0_flag = 0;
}

void setTimer1(int duration)
{
  timer1_counter = duration / TIMER_CYCLE;
  timer1_flag = 0;
}

void setTimer2(int duration)
{
  timer2_counter = duration / TIMER_CYCLE;
  timer2_flag = 0;
}

void timer_run(void)
{
  if (timer0_counter > 0)
  {
    timer0_counter--;

    if (timer0_counter == 0)
    {
      timer0_flag = 1;
    }
  }

  if (timer1_counter > 0)
  {
    timer1_counter--;

    if (timer1_counter == 0)
    {
      timer1_flag = 1;
    }
  }

  if (timer2_counter > 0)
  {
    timer2_counter--;

    if (timer2_counter == 0)
    {
      timer2_flag = 1;
    }
  }
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
void display7SEG(int num);
void show7SEG(uint8_t display, int num);
void update7SEG(int index);

void displayMatrixRows(uint8_t data);
void updateLEDMatrix(int index);
void shiftMatrixLeft(void);


void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);
void timer_run(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Both 7-segment modules are common-anode: RESET turns a segment on. */
static void setSegments(GPIO_PinState a, GPIO_PinState b, GPIO_PinState c,
                        GPIO_PinState d, GPIO_PinState e, GPIO_PinState f,
                        GPIO_PinState g)
{
  HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, a);
  HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, b);
  HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, c);
  HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, d);
  HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, e);
  HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, f);
  HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, g);
}

void display7SEG(int num)
{
  switch (num)
  {
    case 0:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
      break;
    case 1:
      setSegments(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 2:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
      break;
    case 3:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
      break;
    case 4:
      setSegments(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 5:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 6:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 7:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
    case 8:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    case 9:
      setSegments(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                  GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
      break;
    default:
      setSegments(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET,
                  GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET);
      break;
  }
}

void show7SEG(uint8_t display, int num)
{
  /* PNP enables are active-low. Disable all displays before changing data. */
  HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin,
                    GPIO_PIN_SET);
  display7SEG(num);

  switch (display)
  {
    case 0U:
      HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
      break;
    case 1U:
      HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
      break;
    case 2U:
      HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
      break;
    case 3U:
      HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
      break;
    default:
      break;
  }
}

void update7SEG(int index)
{
  switch (index)
  {
    case 0:
      show7SEG(0U, led_buffer[0]);
      break;
    case 1:
      show7SEG(1U, led_buffer[1]);
      break;
    case 2:
      show7SEG(2U, led_buffer[2]);
      break;
    case 3:
      show7SEG(3U, led_buffer[3]);
      break;
    default:
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
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
  updateClockBuffer();

  /* Initial states:
     - PNP 7SEG enables are active-low -> HIGH = off
     - ULN2803 matrix enables are active-high -> LOW = off
     - matrix rows start LOW */
  HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,
                    ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin |
                    ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin,
                    GPIO_PIN_RESET);
  displayMatrixRows(0x00U);

  HAL_TIM_Base_Start_IT(&htim2);

  /* timer0: clock + DOT every 1 second */
  setTimer0(1000);

  /* timer1: scan one 7SEG every 250 ms */
  setTimer1(250);

  /* timer2: scan one LED-matrix column every 1 ms (~125 Hz full frame) */
  setTimer2(1);
  matrix_last_shift_tick = HAL_GetTick();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* timer0: clock and DOT */
    if (timer0_flag == 1)
    {
      setTimer0(1000);

      HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);

      second++;

      if (second >= 60)
      {
        second = 0;
        minute++;

        if (minute >= 60)
        {
          minute = 0;
          hour++;

          if (hour >= 24)
          {
            hour = 0;
          }
        }

        updateClockBuffer();
      }
    }

    /* timer1: 4 seven-segment displays */
    if (timer1_flag == 1)
    {
      setTimer1(250);

      update7SEG(index_led);

      index_led++;

      if (index_led >= MAX_LED)
      {
        index_led = 0;
      }
    }

    /* timer2: 8x8 LED matrix */
    if (timer2_flag == 1)
    {
      setTimer2(1);

      /* Change the image only at the start of a frame. */
      if (index_led_matrix == 0)
      {
        uint32_t now = HAL_GetTick();

        if ((uint32_t)(now - matrix_last_shift_tick) >= MATRIX_SHIFT_PERIOD_MS)
        {
          matrix_last_shift_tick = now;
          shiftMatrixLeft();
        }
      }

      updateLEDMatrix(index_led_matrix);

      index_led_matrix++;

      if (index_led_matrix >= MAX_LED_MATRIX)
      {
        index_led_matrix = 0;
      }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    /* Exercises 9-10: the interrupt only updates software timers. */
    timer_run();
  }
}

void shiftMatrixLeft(void)
{
  uint8_t first_column = matrix_buffer[0];

  for (int column = 0; column < (MAX_LED_MATRIX - 1); column++)
  {
    matrix_buffer[column] = matrix_buffer[column + 1];
  }

  /* Wrap the disappearing column around to the right edge. */
  matrix_buffer[MAX_LED_MATRIX - 1] = first_column;
}

void displayMatrixRows(uint8_t data)
{
  HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin,
                    (data & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin,
                    (data & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin,
                    (data & 0x04U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin,
                    (data & 0x08U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin,
                    (data & 0x10U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin,
                    (data & 0x20U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin,
                    (data & 0x40U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin,
                    (data & 0x80U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void updateLEDMatrix(int index)
{
  /* Blank the matrix while changing columns to avoid ghosting. */
  HAL_GPIO_WritePin(GPIOA,
                    ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin |
                    ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin,
                    GPIO_PIN_RESET);

  displayMatrixRows(0x00U);

  if (index < 0 || index >= MAX_LED_MATRIX)
  {
    return;
  }

  /* Apply the row pattern for the selected column. */
  displayMatrixRows(matrix_buffer[index]);

  /* ULN2803 input HIGH -> transistor ON -> selected matrix column is pulled LOW. */
  switch (index)
  {
    case 0:
      HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, GPIO_PIN_SET);
      break;

    case 1:
      HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, GPIO_PIN_SET);
      break;

    case 2:
      HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, GPIO_PIN_SET);
      break;

    case 3:
      HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, GPIO_PIN_SET);
      break;

    case 4:
      HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, GPIO_PIN_SET);
      break;

    case 5:
      HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, GPIO_PIN_SET);
      break;

    case 6:
      HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, GPIO_PIN_SET);
      break;

    case 7:
      HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, GPIO_PIN_SET);
      break;

    default:
      break;
  }
}




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
