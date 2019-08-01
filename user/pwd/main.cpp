#include <stdio.h>
#include <sys/path.h>

int main()
{
  const char* p = weles::getCurrentPath();
  printf("%s\n", p);
  return 0;
}
