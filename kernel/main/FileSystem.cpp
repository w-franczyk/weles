#include "FileSystem.h"

#include <string.h>

namespace
{

void toLower(char* what, std::size_t size)
{
  constexpr char diff = 'A' - 'a';
  for (std::size_t i = 0; i < size; ++i)
  {
    if (what[i] <= 'Z' && what[i] >= 'A')
    {
      what[i] -= diff;
    }
  }
}

} // anonymous namespace

void FileSystem::fileDelete(const char* path)
{
  f_unlink(path);
}

int FileSystem::fileRead(const char* path,
                         char* outBuf,
                         std::size_t maxSize)
{
  FILINFO fileInfo;
  if (f_stat(path, &fileInfo) != FR_OK)
    return -1;

  if (fileInfo.fsize > maxSize)
    return -2;

  FIL file;
  if (f_open(&file, path, FA_READ) != FR_OK)
    return -3;

  int res;
  if (f_read(&file, outBuf, fileInfo.fsize, reinterpret_cast<unsigned*>(&res)) != FR_OK)
    res = -4;

  f_close(&file);
  return res;
}

int FileSystem::fileWrite(const char* path,
                          const char* buf,
                          std::size_t size)
{
  FIL file;
  if (f_open(&file, path, FA_WRITE | FA_OPEN_APPEND) != FR_OK)
    return -1;

  int res;
  if (f_write(&file, buf, size, reinterpret_cast<unsigned*>(&res)) != FR_OK)
    res = -2;

  f_close(&file);
  return res;
}

void FileSystem::init()
{
  f_mount(&m_fat, "", 0);
}

bool FileSystem::stat(const char* path)
{
  FILINFO fileInfo;
  if (f_stat(path, &fileInfo) == FR_OK)
    return true;

  return false;
}

bool FileSystem::getDirectoryFileList(const char* path,
                                      char* outBuf,
                                      std::size_t outBufSize)
{
  DIR directory;
  FILINFO fileInfo;
  FRESULT res;
  res = f_findfirst(&directory, &fileInfo, path, "*");
  std::size_t bufUsed = 0;
  while (res == FR_OK && fileInfo.fname[0])
  {
    std::size_t nameLen = strlen(fileInfo.fname);
    if (bufUsed + nameLen + 1 > outBufSize)
      return false;

    toLower(fileInfo.fname, nameLen);
    memcpy(outBuf, fileInfo.fname, nameLen);
    outBuf += nameLen;
    *outBuf = ' ';
    ++outBuf;
    bufUsed += nameLen + 1;

    res = f_findnext(&directory, &fileInfo);
  }

  f_closedir(&directory);

  return true;
}
