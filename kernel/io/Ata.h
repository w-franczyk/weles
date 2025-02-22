#pragma once

#include <cstdlib>

class Ata
{
  // Only Primary drive supported
  enum Register : std::uint16_t
  {
    RegData = 0x1f0,
    RegError = 0x1f1,
    RegFeatures = 0x1f1,
    RegSectorCount = 0x1f2,
    RegLbaLow = 0x1f3,
    RegLbaMid = 0x1f4,
    RegLbaHigh = 0x1f5,
    RegDriveHead = 0x1f6,
    RegStatus = 0x1f7,
    RegCommand = 0x1f7
  };

  enum Command
  {
    CmdRead = 0x20,
    CmdWrite = 0x30,
    CmdIdentify = 0xec
  };

  enum StatusBit
  {
    StErrBit = 1,
    StIdxBit = 2,
    StCorrBit = 4,
    StDrqBit = 8,
    StSrvBit = 16,
    StDfBit = 32,
    StRdyBit = 64,
    StBsyBit = 128
  };

  struct DriverIdentifier
  {
    std::uint16_t placeholder1[10];
    char serialNumber[20] = {0};
    std::uint16_t placeholder2[3];
    char firmwareRevision[8];
    char modelNumber[40];
    std::uint16_t placeholder3[20];
    std::uint32_t capacitySectors;
    std::uint16_t placeholder4[12];
    std::uint16_t lba48;
    std::uint16_t placeholder5[172];
  };

public:
  Ata() = default;

  enum class InitStatus
  {
    NoDrivesDetected,
    NoPrimaryMaster,
    NotAtaDevice,
    Error,
    Ok
  };

  enum class Result
  {
    NotInitialized,
    SectorNbTooBig,
    Error,
    Ok
  };

  InitStatus init();
  bool isInitialized() const { return m_initialized; }
  Result read(unsigned int sector, std::uint8_t count, std::uint8_t* outBuff);
  Result write(unsigned int sector, std::uint8_t count, const std::uint8_t* buff);

  DriverIdentifier& test() { return m_driverIdentifier; }

private:
  Result prepareIo(Command cmd, unsigned int sector, std::uint8_t count);
  Result cleanUpIo();

  DriverIdentifier m_driverIdentifier;
  bool m_initialized = false;
};
