#include "Shell.h"

void Shell::keyboardEvent(std::uint8_t /*event*/)
{
  m_vga.print("shell: got event\n");
}
