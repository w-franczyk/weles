#include "StdinController.h"

#include "Key.h"

#include <stdio.h>
#include <string.h>

void StdinController::getLine(char* target)
{
  m_bufferWholeLine = true;
  m_targetBuf = target;
  m_targetBufPos = 0;
}

void StdinController::push(char c)
{
  if (m_bufferWholeLine)
  {
    switch (static_cast<unsigned char>(c))
    {
    case '\n':
      m_processController.setSubprocessIoReadReady();
      m_bufferWholeLine = false;
      break;
    case Key::Backspace:
      if (m_targetBufPos > 0)
      {
        m_targetBuf[--m_targetBufPos] = 0;
      }
      break;
    default:
      m_targetBuf[m_targetBufPos++] = c;
    }
  }
  
  m_processController.stdin(&c, 1);
}
