#pragma once

#include <io/Vga.h>

#include <cstdlib>

class Shell
{
public:
  enum class EventRes
  {
    Meh,
    ImSoProud_LaunchTheMissile
  };

  Shell(Vga& vga) : m_vga(vga) {}

  void init();

  // aaah, keyboardEvent returning an info that the new process
  // should be launched, such amazing, much beauty, wow wow!
  EventRes keyboardEvent(unsigned char event);
  void cleanup();
  const char* getCmd() const { return m_cmdBuffer; }

private:
  void addToBuffer(char c);
  void bufferRetreat();
  void showPrompt();

  char m_cmdBuffer[255];
  std::size_t m_cmdBufferIdx = 0;
  Vga& m_vga;
};
