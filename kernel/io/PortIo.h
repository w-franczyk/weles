#pragma once

#include <cstdlib>

extern "C"
{
  void outb(std::uint16_t port, std::uint8_t value);
  std::uint8_t inb(std::uint16_t port);
  void inwn(std::uint16_t port, std::uint16_t* outBuff, std::size_t count);
  void outwn(std::uint16_t port, const std::uint16_t* buff, std::size_t count);
}
