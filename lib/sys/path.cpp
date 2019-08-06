#include <sys/path.h>
#include <string.h>

extern "C"
{
  extern char sigCurrentPath[255];
}

namespace weles
{

const char* getCurrentPath()
{
  return sigCurrentPath;
}

void getAbsolutePath(const char* relativePath, char* outPath)
{
  if (relativePath[0] != '/')
  {
    const char* currPath = weles::getCurrentPath();
    memcpy(outPath, currPath, strlen(currPath));
    
    if (outPath[strlen(outPath) - 1] != '/')
    {
      outPath[strlen(outPath)] = '/';
    }
    
    memcpy(outPath + strlen(outPath) - 1, relativePath, strlen(relativePath));
  }
  else
  {
    memcpy(outPath, relativePath, strlen(relativePath));
  }
}

void setCurrentPath(const char* path)
{
  memset(sigCurrentPath, 0, sizeof(sigCurrentPath));
  memcpy(sigCurrentPath, path, strlen(path));
}

} // namespace weles
