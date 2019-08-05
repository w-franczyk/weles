#include <io/Ata.h>
#include <io/Ps2Keyboard.h>
#include <io/Vga.h>
#include <main/FileSystem.h>
#include <main/Interrupts.h>
#include <main/Memory.h>
#include <main/ProcessController.h>
#include <main/Res.h>
#include <main/StdinController.h>

#include <stdio.h>

Memory memory;
Ata ata;
bool init(Vga& vga,
          Interrupts& interrupts,
          ProcessController& pcontroller,
          FileSystem& fileSystem,
          Ps2Keyboard& keyboard,
          StdinController& stdinController)
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

  interrupts.init(keyboard, stdinController, fileSystem);

//  memory.init();

  fileSystem.init();
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
  Interrupts interrupts; 
  FileSystem filesystem;

  init(vga,
       interrupts,
       processController,
       filesystem,
       ps2Keyboard,
       stdinController);

  while (Res::run)
  {
    if (processController.isSubprocessLoaded())
      processController.invokeSubprocess();
  }

  return 0;
}
