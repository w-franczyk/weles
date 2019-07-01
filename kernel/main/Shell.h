#pragma once

#include <io/Vga.h>

#include <cstdlib>

class Shell
{
public:
  Shell(Vga& vga) : m_vga(vga) {}

  void init();
  void keyboardEvent(unsigned char event);

private:
  void addToBuffer(char c);
  void bufferRetreat();
  void execCmd();
  void showPrompt();

  char m_cmdBuffer[255];
  std::size_t m_cmdBufferIdx = 0;
  Vga& m_vga;
};
