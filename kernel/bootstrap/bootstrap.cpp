#include <io/Screen.h>

// extern "C" void p();

int bmain()
{
//  p();

  const char* s = "asd";
  Screen screen;
  screen.print(s, 3);

  for (;;)
  {
  }

  return 0;
}
