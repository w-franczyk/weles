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

void setCurrentPath(const char* path)
{
  memset(sigCurrentPath, 0, sizeof(sigCurrentPath));
  memcpy(sigCurrentPath, path, strlen(path));
}

} // namespace weles
