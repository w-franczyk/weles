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

  enum class Mode
  {
    PrintOnly, // print only on keyboard event and do nothing else
    FullService // do all
  };

  Shell(Vga& vga) : m_vga(vga) {}

  void init();

  // aaah, keyboardEvent returning an info that the new process
  // should be launched, such amazing, much beauty, wow wow!
  EventRes keyboardEvent(unsigned char event);
  void cleanup();
  const char* getCmd() const { return m_cmdBuffer; }
  void setMode(Mode mode) { m_mode = mode; }
  void showPrompt();

private:
  void addToBuffer(char c);
  void bufferRetreat();
  EventRes handleActions(unsigned char event);
  void handleVga(unsigned char event);

  char m_cmdBuffer[255];
  std::size_t m_cmdBufferIdx = 0;
  Mode m_mode = Mode::FullService;
  Vga& m_vga;
};
