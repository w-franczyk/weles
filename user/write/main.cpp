#include <stdio.h>
#include <sys/syscall.h>

int main(int argc, char* /*argv*/)
{
  if (argc <= 0)
  {
    printf("Usage:\n");
    printf("write PATH\n\n");
    printf("Example:\n");
    printf("write /misc/zywiolak\n");
  }

  

  return 0;
}
