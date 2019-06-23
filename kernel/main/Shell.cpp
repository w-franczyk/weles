#include "Shell.h"

#include <stdio.h>

void Shell::keyboardEvent(unsigned char event)
{
  printf("Got keyboard: %x\n", event);
}
