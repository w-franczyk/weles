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
  if (argv[0] != '/')
  {
    const char* currPath = weles::getCurrentPath();
    memcpy(path, currPath, strlen(currPath));
    
    if (path[strlen(path) - 1] != '/')
    {
      path[strlen(path)] = '/';
    }
    
    memcpy(path + strlen(path) - 1, argv, strlen(argv));
  }
  else
  {
    memcpy(path, argv, strlen(argv));
  }

  char lineBuf[1024] = {0};
  while (memcmp(lineBuf, ";;wq", 4) != 0)
  {
    sysStdin(lineBuf);
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
