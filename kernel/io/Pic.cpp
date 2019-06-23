#include "Pic.h"

#include "PortIo.h"

void Pic::init()
{
  outb(Pic1PortCmd, PicCmdInit);
  outb(Pic2PortCmd, PicCmdInit);

  // remap IRQ0-7 to 0x20-0x27 in the interrupt vector table
  outb(Pic1PortData, 0x20);
  
  // and do the same with IRQ8-15
  outb(Pic2PortData, 0x28);
  
  // PIC2 via PIC1??? need to find the cause of it
  outb(Pic1PortData, 0x04);
  outb(Pic2PortData, 0x02);
  
  // enable 8086/88 mode
  outb(Pic1PortData, 0x01);
  outb(Pic2PortData, 0x01);

  // mask interrupts
  outb(Pic1PortData, 0xff);
  outb(Pic2PortData, 0xff);
}
