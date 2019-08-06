#include <sys/path.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv)
{
  if (argc <= 0)
  {
    printf("Simple write tool, will read stdin and write it into PATH\n");
    printf("until ';;wq' line appears\n\n");
    printf("Usage:\n");
    printf("write PATH\n\n");
    printf("Example:\n");
    printf("write /misc/zywiolak\n");
    return 0;
  }
  
  char path[1024] = {0};
  weles::getAbsolutePath(argv, path);

  char lineBuf[1024] = {0};
  while (true)
  {
    sysStdin(lineBuf);

    if (memcmp(lineBuf, ";;wq", 4) == 0)
      break;

    lineBuf[strlen(lineBuf)] = '\n';
    int res = sysFileWrite(path, lineBuf, strlen(lineBuf));
    if (res < 0)
    {
      printf("Error: file '%s' write fail: %d\n", path, res);
      break;
    }
    
    memset(lineBuf, 0, sizeof(lineBuf));
  }

  return 0;
}
