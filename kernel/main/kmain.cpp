#include <io/Ata.h>
#include <io/Ps2Keyboard.h>
#include <io/Vga.h>
#include <main/Interrupts.h>
#include <main/Memory.h>
#include <main/ProcessController.h>
#include <main/Res.h>
#include <main/StdinController.h>
#include <thirdparty/fatfs/ff.h>

#include <stdio.h>

Memory memory;
Ata ata;
bool init(Vga& vga, Interrupts& interrupts, ProcessController& pcontroller)
{
  printf("\nI AM THE KERNEL\n\n");
  printf("====================\n");
  printf("= Welcome to Weles =\n");
  printf("====================\n");
  vga.print("VGA Initialized\n");
  vga.print("Initializing ATA controller... ");
  Ata& ata = Res::getAta();
  switch (ata.init())
  {
  case Ata::InitStatus::NoDrivesDetected:
    vga.print("Error: no drives has been detected\n");
    return false;
  case Ata::InitStatus::NoPrimaryMaster:
    vga.print("Error: Primary Master has not been detected\n");
    return false;
  case Ata::InitStatus::NotAtaDevice:
    vga.print("Error: Primary Master is not an ATA device\n");
    return false;
  case Ata::InitStatus::Error:
    vga.print("Error: Failure during Primary Master initialization\n");
    return false;
  default:
    vga.print("Done\n");
  }

  interrupts.init();

//  memory.init();

  auto& di = ata.test();
  di.serialNumber[19] = 0;
  di.firmwareRevision[7] = 0;
  di.modelNumber[39] = 0;
  vga.print("ATA Serial Number: ");
  vga.print(di.serialNumber);
  vga.print("\n");
  vga.print("ATA Firmware: ");
  vga.print(di.firmwareRevision);
  vga.print("\n");
  vga.print("ATA Model: ");
  vga.print(di.modelNumber);
  vga.print("\n");

  std::uint8_t buff[512];
  if (ata.read(2048, 1, buff) == Ata::Result::Ok)
    vga.print("ATA test: Success!\n");
  else
    vga.print("ATA test: Error :(\n");

  FATFS fs;
  f_mount(&fs, "", 0);

  FIL f;
  int res = f_open(&f, "/WRTEST.TXT", FA_READ);
  char resStr[3] = {'W', '\n', 0};
  vga.print("f_open res: ");
  resStr[0] = res + 0x30;
  vga.print(resStr);

  unsigned int bytesRead = 0;
  res = f_read(&f, buff, 5, &bytesRead);
  vga.print("f_read res: ");
  resStr[0] = res + 0x30;
  vga.print(resStr);

  pcontroller.init();

  return true;
}

int kmain()
{
  Vga vga;
  Res::setVga(vga);
  Res::setAta(ata);

  ProcessController processController(vga);
  StdinController stdinController(processController);
  Ps2Keyboard ps2Keyboard(stdinController);
  Interrupts interrupts(ps2Keyboard);
  
  // TODO: probably it shouldn't be here!!
  // Users can use their own references to it, not the global one!
  Res::setKeyboard(ps2Keyboard);

  init(vga, interrupts, processController);
  while (Res::run)
  {
  }

  return 0;
}
