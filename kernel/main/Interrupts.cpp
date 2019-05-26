#include "Interrupts.h"

#include <io/PortIo.h>
#include <io/Vga.h>
#include <main/InterruptDescriptor.h>
#include <main/Res.h>

void Interrupts::init()
{
  initPic();
  initIdt();

  //int a = 5 / 0;
  __asm__("int 0x80");
}

void Interrupts::isrDefault(InterruptFrame*)
{
  /* Res::run = false; */
  // __asm__ ("cli;hlt\n\t");
  Res::getVga().print("interrupt!!!!\n");
}

void Interrupts::initIdt()
{
  m_idt[Int00DivideError] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int01Debug] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int02Nmi] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int03Breakpoint] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int04Overflow] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int05BoundsCheck] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int06InvalidOpcode] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int07CoprocessorNotAvail] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int08DoubleFault] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int09CoprocessorOverrun] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0aInvalidTss] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0bSegmentNotPresent] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0cStackException] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0dProtectionException] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0ePageFault] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int0f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int10CoprocessorError] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int11] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int12] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int13] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int14] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int15] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int16] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int17] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int18] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int19] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int1f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int20Irq0Timer] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int21Irq1Keyboard] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int22Irq2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int23Irq3Com2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int24Irq4Com1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int25Irq5Lpt2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int26Irq6Floppy] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int27Irq7Lpt1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int28Irq8Cmos] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int29Irq9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2aIrq10] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2bIrq11] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2cIrq12Ps2Mouse] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2dIrq13Coprocessor] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2eIrq14Ide0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int2fIrq15Ide1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int30] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int31] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int32] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int33] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int34] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int35] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int36] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int37] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int38] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int39] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int3f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int40] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int41] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int42] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int43] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int44] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int45] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int46] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int47] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int48] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int49] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int4f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int50] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int51] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int52] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int53] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int54] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int55] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int56] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int57] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int58] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int59] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int5f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int60] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int61] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int62] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int63] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int64] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int65] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int66] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int67] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int68] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int69] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int6f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int70] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int71] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int72] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int73] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int74] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int75] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int76] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int77] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int78] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int79] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int7f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int80] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int81] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int82] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int83] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int84] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int85] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int86] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int87] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int88] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int89] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int8f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int90] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int91] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int92] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int93] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int94] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int95] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int96] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int97] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int98] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int99] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9a] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9b] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9c] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9d] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9e] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[Int9f] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntA9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntAf] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntB9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntBf] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntC9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntCf] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntD9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntDf] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntE9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntEf] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF0] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF1] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF2] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF3] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF4] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF5] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF6] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF7] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF8] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntF9] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFa] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFb] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFc] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFd] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFe] = InterruptDescriptor(Interrupts::isrDefault).serialize();
  m_idt[IntFf] = InterruptDescriptor(Interrupts::isrDefault).serialize();

  m_idtPtr.size = sizeof(m_idt) - 1;
  m_idtPtr.ptr = m_idt;

  __asm__("lidt %0" :: "m"(m_idtPtr));
}

void Interrupts::initPic()
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

  // disable PIC to use APIC ??
  outb(Pic1PortData, 0xff);
  outb(Pic2PortData, 0xff);
}
