#include "Shell.h"

#include "Key.h"

#include <stdio.h>
#include <string.h>

void Shell::init()
{
  printf("Skorupa Welosa v0.1\n");
  showPrompt();
}

void Shell::keyboardEvent(unsigned char event)
{
  if (event > Key::SpecialKeysStart)
  {
    if (event == Key::Backspace)
    {
      m_vga.retreat();
      bufferRetreat();
    }
  }
  else
  {
    printf("%c", event);

    if (event == '\n')
    {
      execCmd();
    }
    else
    {
      addToBuffer(event);
    }
  }
}

void Shell::addToBuffer(char c)
{
  if (m_cmdBufferIdx < sizeof(m_cmdBuffer))
  {
    m_cmdBuffer[m_cmdBufferIdx++] = c;
  }
}

void Shell::bufferRetreat()
{
  m_cmdBuffer[m_cmdBufferIdx] = 0;
  if (m_cmdBufferIdx > 0)
    --m_cmdBufferIdx;
}

void Shell::execCmd()
{
  printf("System: Executing command: %s\n", m_cmdBuffer);
  memset(m_cmdBuffer, 0, sizeof(m_cmdBuffer));
  m_cmdBufferIdx = 0;
  showPrompt();
}

void Shell::showPrompt()
{
  printf("$ ");
}
