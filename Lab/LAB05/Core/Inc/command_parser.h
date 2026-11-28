#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>

typedef enum
{
  LAB5_CMD_NONE,
  LAB5_CMD_RST,
  LAB5_CMD_OK
} Lab5Command;

void CommandParser_Reset(void);
Lab5Command CommandParser_Push(uint8_t byte);

#endif
