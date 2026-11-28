#include "command_parser.h"
#include <string.h>

typedef enum
{
  WAIT_START,
  READ_COMMAND
} ParserState;

static ParserState state = WAIT_START;
static char command_text[3];
static uint8_t length;

void CommandParser_Reset(void)
{
  state = WAIT_START;
  length = 0;
}

Lab5Command CommandParser_Push(uint8_t byte)
{
  if (byte == '!')
  {
    state = READ_COMMAND;
    length = 0;
    return LAB5_CMD_NONE;
  }
  if (state == WAIT_START)
  {
    return LAB5_CMD_NONE;
  }

  if (byte == '#')
  {
    Lab5Command command = LAB5_CMD_NONE;
    if (length == 3U && memcmp(command_text, "RST", 3U) == 0)
    {
      command = LAB5_CMD_RST;
    }
    else if (length == 2U && memcmp(command_text, "OK", 2U) == 0)
    {
      command = LAB5_CMD_OK;
    }
    CommandParser_Reset();
    return command;
  }

  if (length == sizeof(command_text))
  {
    CommandParser_Reset();
  }
  else
  {
    command_text[length++] = (char)byte;
  }
  return LAB5_CMD_NONE;
}
