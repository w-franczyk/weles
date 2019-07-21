#include "ProcessController.h"

#include <stdio.h>

void ProcessController::invokeSubprocess()
{
  void (*cmd)() = reinterpret_cast<void(*)()>(0x100400);
  cmd();
  m_subprocessLoaded = false;
  m_shell.showPrompt();
}

void ProcessController::stdin(const char* buff, std::size_t /*size*/)
{
  if (m_shell.keyboardEvent(buff[0]) == Shell::EventRes::ImSoProud_LaunchTheMissile)
  {
    char binaryName[256] = {0};
    snprintf(binaryName, sizeof(binaryName), "/bin/%s", m_shell.getCmd());

    if (loadCmd(binaryName))
    {
      m_subprocessLoaded = true;
    }
    else
    {
      // error printed, just get to the next shell line
      m_shell.showPrompt();
    }

    m_shell.cleanup();
  }
}

bool ProcessController::loadCmd(const char* path)
{
  FILINFO fileInfo;
  FRESULT statRes = f_stat(path, &fileInfo);
  if (statRes == FR_NO_FILE)
  {
    printf("Error: command '%s' does not exist\n", m_shell.getCmd());
    return false;
  }
  
  if (statRes != FR_OK)
  {
    printf("Fatal error: kernel failed to stat the command\n");
    return false;
  }

  FIL binary;
  if (f_open(&binary, path, FA_READ) != FR_OK)
  {
    printf("Fatal error: kernel failed to open the binary");
    return false;
  }

  unsigned dataRead = 0;
  if (f_read(&binary, m_subprocessAddr, fileInfo.fsize, &dataRead) != FR_OK)
  {
    printf("Fatal error: kernel failed to read the binary");
    return false;
  }

  if (dataRead != fileInfo.fsize)
  {
    printf("Fatal error: read not the whole command");
    return false;
  }

  return true;
}
