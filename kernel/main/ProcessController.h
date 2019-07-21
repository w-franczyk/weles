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

  bool isSubprocessLoaded() const { return m_subprocessLoaded; }
  void invokeSubprocess();
  void stdin(const char* buff, std::size_t /*size*/);

private:
  bool loadCmd(const char* path);

  Shell m_shell;
  void* m_subprocessAddr = reinterpret_cast<void*>(0x100000);
  bool m_subprocessLoaded = false;
};
