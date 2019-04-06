#include "Vga.h"

#include <io/PortIo.h>


Vga::Vga()
{
  initCursorPos();
}

void Vga::initCursorPos()
{
  std::uint16_t pos = inb(0);
  m_framePtr = m_frameBuffer + pos * 2; // 2 bytes per one cell
}

std::uint16_t Vga::getCursorPos() const
{
  return (m_framePtr - m_frameBuffer) / 2;
}

void Vga::print(const char* s)
{
  LineParams params;
  print(s, params);
}

void Vga::print(const char* s, Color fgcolor)
{
  LineParams params;
  params.fgcolor = fgcolor;
  print(s, params);
}

void Vga::print(const char* s, Color fgcolor, Color bgcolor)
{
  LineParams params;
  params.fgcolor = fgcolor;
  params.bgcolor = bgcolor;
  print(s, params);
}

void Vga::print(const char* s, const LineParams& params)
{
  const std::uint8_t paramsValue = getParamsValue(params);
  while (*s != 0)
  {
    *(m_framePtr++) = *s++;
    *(m_framePtr++) = paramsValue;
  }
  
  poll();
}

void Vga::poll() const
{
  std::uint16_t pos = getCursorPos();
  outb(PortCommand, CmdMoveCursorHigh);
  outb(PortData, pos >> 8);
  outb(PortCommand, CmdMoveCursorLow);
  outb(PortData, pos & 0x00FF);
}

std::uint8_t Vga::getParamsValue(const LineParams& params) const
{
  return params.blinking << 7 |
         static_cast<std::uint8_t>(params.bgcolor) << 4 |
         params.bright << 3 |
         static_cast<std::uint8_t>(params.fgcolor);
}
