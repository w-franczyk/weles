#pragma once

#include <cstdlib>

// TODO: instead of sharing Port and Cmd enums
// Pic class could provide a proper interface to 
// cooperate with PIC1 and PIC2
class Pic
{
public:
  enum Port : std::uint16_t
  {
    Pic1PortCmd = 0x20,
    Pic1PortData = 0x21,
    Pic2PortCmd = 0xa0,
    Pic2PortData = 0xa1
  };

  enum Cmd : std::uint8_t
  {
    PicCmdInit = 0x11,
    PicCmdAck = 0x20
  };

  Pic() = default;
  void init();
};
