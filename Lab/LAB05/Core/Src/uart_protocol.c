#include "uart_protocol.h"
#include <stdio.h>

#define ACK_TIMEOUT_MS 3000U
#define TX_TIMEOUT_MS  50U

typedef enum
{
  WAIT_REQUEST,
  WAIT_ACK
} ProtocolState;

static ProtocolState state = WAIT_REQUEST;
static char packet[sizeof("!ADC=4294967295#\r\n")];
static uint16_t packet_length;
static uint32_t sent_at;

static void send_packet(UART_HandleTypeDef *uart)
{
  HAL_UART_Transmit(uart, (uint8_t *)packet, packet_length, TX_TIMEOUT_MS);
  sent_at = HAL_GetTick();
}

void UartProtocol_Run(UART_HandleTypeDef *uart, ADC_HandleTypeDef *adc, Lab5Command command)
{
  switch (state)
  {
    case WAIT_REQUEST:
      if (command == LAB5_CMD_RST)
      {
        /* Trigger a fresh sample for each new request, not for retries. */
        if (HAL_ADC_Start(adc) != HAL_OK)
        {
          break;
        }
        if (HAL_ADC_PollForConversion(adc, 10U) != HAL_OK)
        {
          HAL_ADC_Stop(adc);
          break;
        }
        unsigned long value = (unsigned long)HAL_ADC_GetValue(adc);
        HAL_ADC_Stop(adc);
        packet_length = (uint16_t)snprintf(packet, sizeof(packet), "!ADC=%lu#\r\n", value);
        send_packet(uart);
        state = WAIT_ACK;
      }
      break;

    case WAIT_ACK:
      if (command == LAB5_CMD_OK)
      {
        state = WAIT_REQUEST;
      }
      else if (HAL_GetTick() - sent_at >= ACK_TIMEOUT_MS)
      {
        send_packet(uart);
      }
      break;
  }
}
