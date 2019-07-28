#include "StdinController.h"

#include <stdio.h>
#include <string.h>

void StdinController::getLine(char* target)
{
  m_waitForWholeLine = true;

  /* int c = 1; */
  // interrupts handling (push func) should set it to false
  // once we get the whole line
  /* while (m_waitForWholeLine) */
  /* { */
  /*   int a = 2; */
  /*   int b = a; */
  /*   a = c; */
  /*   b = c; */
  /*   c = 14; */
  /*   c = b; */
  /* } */

  memcpy(target, m_buffer, strlen(m_buffer));
  memset(m_buffer, 0, m_bufferPos);
  m_bufferPos = 0;
}

void StdinController::push(char c)
{
  if (m_waitForWholeLine)
  {
    if (m_bufferPos < sizeof(m_buffer))
    {
      if (c == '\n')
      {
        m_waitForWholeLine = false;
      }
      else
      {
        m_buffer[m_bufferPos++] = c;
      }
    }
    else
    {
      m_buffer[sizeof(m_buffer) - 1] = 0;
      m_waitForWholeLine = false;
    }
  }
  else
  {
    m_processController.stdin(&c, 1);
  }
}
