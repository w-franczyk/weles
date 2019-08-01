#include <sys/path.h>

extern "C"
{
  extern char* sigCurrentPath;
}

namespace weles
{

const char* getCurrentPath()
{
  return sigCurrentPath;
}

} // namespace weles
