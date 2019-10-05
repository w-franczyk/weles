#include <sys/path.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char* argv)
{
  if (argc <= 0)
  {
    printf("Remove file if you need.\n\n");
    printf("Usage:\n");
    printf("cat PATH\n\n");
    printf("Example:\n");
    printf("cat /misc/zoriuszka\n");
    return 0;
  }
  
  char path[1024] = {0};
  weles::getAbsolutePath(argv, path);
  sysFileDelete(path);

  return 0;
}
