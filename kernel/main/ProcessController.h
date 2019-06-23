#pragma once

#include "Shell.h"

#include <io/Vga.h>

class ProcessController
{
public:
  // TODO: ProcessController needing Vga, weird right?
  // Need to change it Shell will be just a separate process,
  // not a "special" one
  explicit ProcessController(Vga& vga) : m_shell(Shell(vga)) {}

  void stdin(std::uint8_t* buff, std::size_t /*size*/)
  {
    m_shell.keyboardEvent(buff[0]);
  }

private:
  Shell m_shell;
};
