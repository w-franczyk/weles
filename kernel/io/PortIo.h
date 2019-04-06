#pragma once

#include <libk/cstdlib>

extern "C"
{
  void outb(std::uint16_t port, std::uint8_t value);
  std::uint8_t inb(std::uint16_t port);
}
