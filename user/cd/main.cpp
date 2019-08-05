#include <sys/path.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char* argv)
{
  if (argc <= 0)
  {
    weles::setCurrentPath("/");
  }
  else if (sysStat(argv))
  {
    weles::setCurrentPath(argv);
  }
  else
  {
    printf("Can't find: %s\n", argv);
    return 1;
  }

  return 0;
}
