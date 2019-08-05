#pragma once

#include "FileSystem.h"
#include "InterruptFrame.h"
#include "StdinController.h"

#include <io/Pic.h>
#include <io/Ps2Keyboard.h>

#include <cstdlib>

class Interrupts
{
  enum Int : std::uint8_t
  {
    Int00DivideError = 0,
    Int01Debug,
    Int02Nmi,
    Int03Breakpoint,
    Int04Overflow,
    Int05BoundsCheck,
    Int06InvalidOpcode,
    Int07CoprocessorNotAvail,
    Int08DoubleFault,
    Int09CoprocessorOverrun,
    Int0aInvalidTss,
    Int0bSegmentNotPresent,
    Int0cStackException,
    Int0dProtectionException,
    Int0ePageFault,
    Int0f,
    Int10CoprocessorError,
    Int11,
    Int12,
    Int13,
    Int14,
    Int15,
    Int16,
    Int17,
    Int18,
    Int19,
    Int1a,
    Int1b,
    Int1c,
    Int1d,
    Int1e,
    Int1f,
    Int20Irq0Timer,
    Int21Irq1Keyboard,
    Int22Irq2,
    Int23Irq3Com2,
    Int24Irq4Com1,
    Int25Irq5Lpt2,
    Int26Irq6Floppy,
    Int27Irq7Lpt1,
    Int28Irq8Cmos,
    Int29Irq9,
    Int2aIrq10,
    Int2bIrq11,
    Int2cIrq12Ps2Mouse,
    Int2dIrq13Coprocessor,
    Int2eIrq14Ide0,
    Int2fIrq15Ide1,
    Int30,
    Int31,
    Int32,
    Int33,
    Int34,
    Int35,
    Int36,
    Int37,
    Int38,
    Int39,
    Int3a,
    Int3b,
    Int3c,
    Int3d,
    Int3e,
    Int3f,
    Int40,
    Int41,
    Int42,
    Int43,
    Int44,
    Int45,
    Int46,
    Int47,
    Int48,
    Int49,
    Int4a,
    Int4b,
    Int4c,
    Int4d,
    Int4e,
    Int4f,
    Int50,
    Int51,
    Int52,
    Int53,
    Int54,
    Int55,
    Int56,
    Int57,
    Int58,
    Int59,
    Int5a,
    Int5b,
    Int5c,
    Int5d,
    Int5e,
    Int5f,
    Int60,
    Int61,
    Int62,
    Int63,
    Int64,
    Int65,
    Int66,
    Int67,
    Int68,
    Int69,
    Int6a,
    Int6b,
    Int6c,
    Int6d,
    Int6e,
    Int6f,
    Int70,
    Int71,
    Int72,
    Int73,
    Int74,
    Int75,
    Int76,
    Int77,
    Int78,
    Int79,
    Int7a,
    Int7b,
    Int7c,
    Int7d,
    Int7e,
    Int7f,
    Int80,
    Int81,
    Int82,
    Int83,
    Int84,
    Int85,
    Int86,
    Int87,
    Int88,
    Int89,
    Int8a,
    Int8b,
    Int8c,
    Int8d,
    Int8e,
    Int8f,
    Int90,
    Int91,
    Int92,
    Int93,
    Int94,
    Int95,
    Int96,
    Int97,
    Int98,
    Int99,
    Int9a,
    Int9b,
    Int9c,
    Int9d,
    Int9e,
    Int9f,
    IntA0,
    IntA1,
    IntA2,
    IntA3,
    IntA4,
    IntA5,
    IntA6,
    IntA7,
    IntA8,
    IntA9,
    IntAa,
    IntAb,
    IntAc,
    IntAd,
    IntAe,
    IntAf,
    IntB0,
    IntB1,
    IntB2,
    IntB3,
    IntB4,
    IntB5,
    IntB6,
    IntB7,
    IntB8,
    IntB9,
    IntBa,
    IntBb,
    IntBc,
    IntBd,
    IntBe,
    IntBf,
    IntC0,
    IntC1,
    IntC2,
    IntC3,
    IntC4,
    IntC5,
    IntC6,
    IntC7,
    IntC8,
    IntC9,
    IntCa,
    IntCb,
    IntCc,
    IntCd,
    IntCe,
    IntCf,
    IntD0,
    IntD1,
    IntD2,
    IntD3,
    IntD4,
    IntD5,
    IntD6,
    IntD7,
    IntD8,
    IntD9,
    IntDa,
    IntDb,
    IntDc,
    IntDd,
    IntDe,
    IntDf,
    IntE0,
    IntE1,
    IntE2,
    IntE3,
    IntE4,
    IntE5,
    IntE6,
    IntE7,
    IntE8,
    IntE9,
    IntEa,
    IntEb,
    IntEc,
    IntEd,
    IntEe,
    IntEf,
    IntF0,
    IntF1,
    IntF2,
    IntF3,
    IntF4,
    IntF5,
    IntF6,
    IntF7,
    IntF8,
    IntF9,
    IntFa,
    IntFb,
    IntFc,
    IntFd,
    IntFe,
    IntFf
  };

#pragma pack(push, 1)
  struct IdtPtr
  {
    std::uint16_t size;
    std::uint64_t* ptr;
  };
#pragma pack(pop)

public:
  Interrupts() {}

  void init(Ps2Keyboard& keyboard,
            StdinController& stdinController,
            FileSystem& fileSystem);

  __attribute__((interrupt)) static void
  isrDefault(InterruptFrame*);
 
  __attribute__((interrupt)) static void
  isrSyscall(InterruptFrame*);
  
  __attribute__((interrupt)) static void
  isrException00Divide(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException01Debug(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException02Nmi(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException03Breakpoint(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException04Overflow(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException05BoundsCheck(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException06InvalidOpcode(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException07CoprocessorNotAvail(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException08DoubleFault(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException09CoprocessorOverrun(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0aInvalidTss(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0bSegmentNotPresent(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0cStack(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0dProtection(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0ePageFault(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException0f(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrException10CoprocessorError(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq0Timer(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq1Keyboard(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq2(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq3Com2(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq4Com1(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq5Lpt2(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq6Floppy(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq7Lpt1(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq8Cmos(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq9(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq10(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq11(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq12Ps2Mouse(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq13Coprocessor(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq14Ide0(InterruptFrame*);

  __attribute__((interrupt)) static void
  isrIrq15Ide1(InterruptFrame*);

private:
  void initIdt();
  void initPic();
  void unmaskHandledIrqs();

  std::uint64_t m_idt[256];
  IdtPtr m_idtPtr;
  Pic m_pic;
  
  static FileSystem* m_fileSystem;
  static Ps2Keyboard* m_ps2Keyboard;
  static StdinController* m_stdinController;
};
