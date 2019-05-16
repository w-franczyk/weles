#include "Interrupts.h"

#include <io/PortIo.h>

void Interrupts::init()
{
  initPic();
}

void Interrupts::initPic()
{
  outb(Pic1PortCmd, PicCmdInit);
  outb(Pic2PortCmd, PicCmdInit);

  // remap IRQ0-7 to 0x20-0x27 in the interrupt vector table
  outb(Pic1PortData, 0x20);
  
  // and do the same with IRQ8-15
  outb(Pic2PortData, 0x28);
}
