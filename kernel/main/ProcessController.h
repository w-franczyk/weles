#pragma once

#include "Shell.h"

#include <io/Vga.h>

#include <thirdparty/fatfs/ff.h>

class ProcessController
{
public:
  // TODO: ProcessController needing Vga, weird right?
  // Need to change it Shell will be just a separate process,
  // not a "special" one
  explicit ProcessController(Vga& vga) : m_shell(Shell(vga)) {}

  void init()
  {
    m_shell.init();
  }

  void stdin(const char* buff, std::size_t /*size*/);

private:
  Shell m_shell;
  void* m_subProcessAddr = reinterpret_cast<void*>(0x100000);
};
