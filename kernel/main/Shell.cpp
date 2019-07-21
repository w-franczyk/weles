#include "Shell.h"

#include "Key.h"

#include <stdio.h>
#include <string.h>

void Shell::init()
{
  printf("Skorupa Welesa v0.2\n");
  showPrompt();
}

auto Shell::keyboardEvent(unsigned char event) -> EventRes
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
      if (m_cmdBufferIdx > 0)
        return EventRes::ImSoProud_LaunchTheMissile;
      else
        showPrompt();
    }
    else
    {
      addToBuffer(event);
    }
  }

  return EventRes::Meh;
}

void Shell::cleanup()
{
  memset(m_cmdBuffer, 0, sizeof(m_cmdBuffer));
  m_cmdBufferIdx = 0;
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
  if (m_cmdBufferIdx > 0)
    --m_cmdBufferIdx;
  
  m_cmdBuffer[m_cmdBufferIdx] = 0;
}

void Shell::showPrompt()
{
  printf("$ ");
}
