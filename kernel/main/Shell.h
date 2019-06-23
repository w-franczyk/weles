#pragma once

#include <io/Vga.h>

#include <cstdlib>

class Shell
{
public:
  Shell(Vga& vga) : m_vga(vga) {}

  void keyboardEvent(std::uint8_t /*event*/);

private:
  Vga& m_vga;
};
