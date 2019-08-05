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
    *m_subprocessSig = SubprocessSig();
    saveEnvVars();
  }

  bool isSubprocessLoaded() const { return m_subprocessLoaded; }
  void invokeSubprocess();
  void setSubprocessIoReadReady() { m_subprocessSig->ioReadReady = 1; }
  void stdin(const char* buff, std::size_t /*size*/);

private:
#pragma pack(push, 1)
  struct SubprocessSig
  {
    SubprocessSig()
    {
      // update other files when need to change
      static_assert(sizeof(SubprocessSig) <= 512);
    }

    std::uint8_t ioReadReady = 0; // set to 1 when stdin/disk read data ready to read
    std::uint8_t argc = 0; // for now always 1 as 1 argument permitted
    char argv[255] = {0};
    char currentPath[255] = "/"; // operated by the user space
  };
#pragma pack(pop)

  bool loadCmd(const char* path);
  void loadEnvVars();
  void saveEnvVars();

  char m_envPath[255] = {0};
  Shell m_shell;
  void* m_subprocessAddr = reinterpret_cast<void*>(0x100000);
  SubprocessSig* m_subprocessSig = reinterpret_cast<SubprocessSig*>(0x100400);
  void(*m_subprocessStartAddr)() = reinterpret_cast<void(*)()>(0x100600);
  bool m_subprocessLoaded = false;
};
