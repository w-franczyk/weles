#include "Ata.h"

#include <io/Pic.h>
#include <io/PortIo.h>
#include <io/Vga.h>
#include <cstdlib>

Ata::InitStatus Ata::init()
{
  if (m_initialized)
    return InitStatus::Ok;

  constexpr unsigned noDrivesByte = 0xff;
  if (inb(RegStatus) == noDrivesByte)
    return InitStatus::NoDrivesDetected;

  // select primary master (the only supported for now) and LBA mode
  constexpr unsigned masterDriveBit = 0xa0;
  constexpr unsigned lbaModeBit = 0x40;
  outb(RegDriveHead, masterDriveBit | lbaModeBit);

  // ATA specs says that it's good to give some time to the drive before
  // executing a next command once the drive selection has been performed.
  // They suggest to read the status 5 times, the last one is real status
  // value. Despite that we don't need the status now, let's wait for the
  // selection to finish. Just to be sure, we're not in hurry now.
  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  
  // reset sector selectors 
  outb(RegSectorCount, 0);
  outb(RegLbaLow, 0);
  outb(RegLbaMid, 0);
  outb(RegLbaHigh, 0);
  
  // identify
  outb(RegCommand, CmdIdentify);
  if (inb(RegStatus) == 0)
    return InitStatus::NoPrimaryMaster;

  // wait for not busy
  while ((inb(RegStatus) & StBsyBit) != 0);

  if (inb(RegLbaMid) != 0 || inb(RegLbaHigh) != 0)
    return InitStatus::NotAtaDevice;

  // wait for the drive finish initialization until done or err
  while ((inb(RegStatus) & StDrqBit) == 0 &&
         (inb(RegStatus) & StErrBit) == 0);

  if (inb(RegStatus) & StErrBit)
    return InitStatus::Error;

  inwn(RegData,
       reinterpret_cast<std::uint16_t*>(&m_driverIdentifier),
       sizeof(DriverIdentifier) / sizeof(std::uint16_t));

  m_initialized = true;
  return InitStatus::Ok;
}

Ata::Result Ata::read(unsigned int sector, std::uint8_t count, std::uint8_t* outBuff)
{
  if (!m_initialized)
    return Result::NotInitialized;

  if (sector > 0x0fffffff) // only Lba28 supported so far
    return Result::SectorNbTooBig;

  outb(RegSectorCount, count);
  outb(RegLbaLow, sector);
  outb(RegLbaMid, sector >> 8);
  outb(RegLbaHigh, sector >> 16);

  outb(RegCommand, CmdRead);
  
  while ((inb(RegStatus) & StDrqBit) == 0 &&
         (inb(RegStatus) & StErrBit) == 0);

  inwn(RegData,
       reinterpret_cast<std::uint16_t*>(outBuff),
       count * 512 / sizeof(std::uint16_t));

  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  if (inb(RegStatus) & StErrBit)
    return Result::Error;
  
  outb(Pic::Pic1PortCmd, Pic::PicCmdAck);
  outb(Pic::Pic2PortCmd, Pic::PicCmdAck);

  return Result::Ok;
}

Ata::Result Ata::write(unsigned int sector, std::uint8_t count, const std::uint8_t* buff)
{
  if (!m_initialized)
    return Result::NotInitialized;

  if (sector > 0x0fffffff) // only Lba28 supported so far
    return Result::SectorNbTooBig;

  outb(RegSectorCount, count);
  outb(RegLbaLow, sector);
  outb(RegLbaMid, sector >> 8);
  outb(RegLbaHigh, sector >> 16);

  outb(RegCommand, CmdWrite);
  
  while ((inb(RegStatus) & StDrqBit) == 0 &&
         (inb(RegStatus) & StErrBit) == 0);

  outwn(RegData,
        reinterpret_cast<const std::uint16_t*>(buff),
        count * 512 / sizeof(std::uint16_t));

  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  inb(RegStatus);
  if (inb(RegStatus) & StErrBit)
    return Result::Error;

  return Result::Ok;
}
