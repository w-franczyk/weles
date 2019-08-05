#include <sys/path.h>
#include <sys/syscall.h>
#include <stdio.h>

int main()
{
  char dirContents[1024] = {0};
  sysGetDirContents(weles::getCurrentPath(), dirContents, sizeof(dirContents));
  printf("%s\n", dirContents);
  return 0;
}
