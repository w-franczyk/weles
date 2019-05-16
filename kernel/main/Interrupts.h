#pragma once

#include <libk/cstdlib>

class Interrupts
{
  enum PicPort : std::uint16_t
  {
    Pic1PortCmd = 0x20,
    Pic1PortData = 0x21,
    Pic2PortCmd = 0xa0,
    Pic2PortData = 0xa1
  };

  enum PicCmd : std::uint8_t
  {
    PicCmdInit = 0x11
  }

public:
  Interrupts() = default;
  bool init();

private:
  initPic();
};
