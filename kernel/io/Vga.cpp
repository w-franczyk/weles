#include "Vga.h"

#include <io/PortIo.h>


Vga::Vga()
{
  initCursorPos();
}

void Vga::initCursorPos()
{
  outb(PortVgaResource, ResCursorPosHigh);
  std::uint16_t pos = inb(PortVgaData) << 8;
  outb(PortVgaResource, ResCursorPosLow);
  pos |= inb(PortVgaData);
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
    switch (*s)
    {
    case '\n':
      m_framePtr += (m_columns - (getCursorPos() % m_columns)) * 2;
      break;
    default:
      *(m_framePtr++) = *s;
      *(m_framePtr++) = paramsValue;
      break;
    }

    // not needed for now
    /* if (getCursorPos() > m_lines * m_columns) */
    /*   addLine(); */

    ++s;
  }
  
  poll();
}

void Vga::poll() const
{
  std::uint16_t pos = getCursorPos();
  outb(PortVgaResource, ResCursorPosHigh);
  outb(PortVgaData, pos >> 8);
  outb(PortVgaResource, ResCursorPosLow);
  outb(PortVgaData, pos & 0x00FF);
}

void Vga::addLine()
{
  /* memcpy(m_frameBuffer, */
  /*        m_frameBuffer + m_columns * 2, */
  /*        m_frameBuffer + m_columns * m_lines * 2 - m_columns * 2); */
}

std::uint8_t Vga::getParamsValue(const LineParams& params) const
{
  return params.blinking << 7 |
         static_cast<std::uint8_t>(params.bgcolor) << 4 |
         params.bright << 3 |
         static_cast<std::uint8_t>(params.fgcolor);
}
