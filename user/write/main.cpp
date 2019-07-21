#include <stdio.h>
#include <sys/syscall.h>

int main()
{
  printf("Witaj!\n");
  printf("Podaj imie: ");
  char imie[256] = {0};
  sysStdin(imie);
  printf("Twoje imie to %s!");

  return 0;
}
