#pragma once

#include <thirdparty/fatfs/ff.h>

#include <cstdlib>

class FileSystem
{
public:
  FileSystem() = default;

  void fileDelete(const char* path);
  int fileRead(const char* path,
               char* outBuf,
               std::size_t maxSize);
  int fileWrite(const char* path,
                const char* buf,
                std::size_t size);
  void init();
  bool getDirectoryFileList(const char* path,
                            char* outBuf,
                            std::size_t outBufSize);
  bool stat(const char* path);

private:
  FATFS m_fat;
};
