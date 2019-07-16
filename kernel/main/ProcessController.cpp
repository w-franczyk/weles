#include "ProcessController.h"

#include <stdio.h>

void ProcessController::stdin(const char* buff, std::size_t /*size*/)
{
  if (m_shell.keyboardEvent(buff[0]) == Shell::EventRes::ImSoProud_LaunchTheMissile)
  {
    char binaryName[256] = {0};
    snprintf(binaryName, sizeof(binaryName), "/bin/%s", m_shell.getCmd());

    FILINFO fileInfo;
    FRESULT statRes = f_stat(binaryName, &fileInfo);
    if (statRes == FR_OK)
    {
      FIL binary;
      if (f_open(&binary, binaryName, FA_READ) == FR_OK)
      {
        unsigned dataRead = 0;
        if (f_read(&binary, m_subProcessAddr, fileInfo.fsize, &dataRead) == FR_OK)
        {
          if (dataRead == fileInfo.fsize)
          {
            void (*cmd)() = reinterpret_cast<void(*)()>(0x100400);
            cmd();
          }
          else
          {
            printf("Fatal error: read not the whole command");
          }
        }
        else
        {
          printf("Fatal error: kernel failed to read the binary");
        }
      }
      else
      {
        printf("Fatal error: kernel failed to open the binary");
      }
    }
    else if (statRes == FR_NO_FILE)
    {
      printf("Error: command '%s' does not exist\n", m_shell.getCmd());
    }
    else
    {
      printf("Fatal error: kernel failed to stat the command\n");
    }

    m_shell.cleanup();
  }
}
