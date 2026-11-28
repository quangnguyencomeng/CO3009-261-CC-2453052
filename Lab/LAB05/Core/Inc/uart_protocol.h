#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include "command_parser.h"
#include "stm32f1xx_hal.h"

void UartProtocol_Run(UART_HandleTypeDef *uart, ADC_HandleTypeDef *adc, Lab5Command command);

#endif
