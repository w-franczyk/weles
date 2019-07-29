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
  void setSubprocessIoReadReady() { m_subprocessSig->ioReadReady = 0; }
  void stdin(const char* buff, std::size_t /*size*/);

private:
  struct SubprocessSig
  {
    SubprocessSig()
    {
      // update other files when need to change
      static_assert(sizeof(SubprocessSig) <= 512);
    }

    std::uint8_t ioReadReady; // set to 1 when stdin/disk read data ready to read 
  };

  bool loadCmd(const char* path);

  Shell m_shell;
  void* m_subprocessAddr = reinterpret_cast<void*>(0x100000);
  SubprocessSig* m_subprocessSig = reinterpret_cast<SubprocessSig*>(0x100400);
  void(*m_subprocessStartAddr)() = reinterpret_cast<void(*)()>(0x100600);
  bool m_subprocessLoaded = false;
};
