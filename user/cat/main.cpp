#include <sys/path.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char* argv)
{
  if (argc <= 0)
  {
    printf("Simple read tool, will read from PATH and write it into stdin\n\n");
    printf("Usage:\n");
    printf("cat PATH\n\n");
    printf("Example:\n");
    printf("cat /misc/zoriuszka\n");
    return 0;
  }
  
  char path[1024] = {0};
  weles::getAbsolutePath(argv, path);

  char fileBuf[1024] = {0};
  int res = sysFileRead(path, fileBuf, sizeof(fileBuf));
  if (res < 0)
  {
    printf("Error: file '%s' read fail: %d\n", path, res);
    return 1;
  }

  printf("%s\n", fileBuf);

  return 0;
}
