#include "Vga.h"

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
    *(m_frameBuff++) = *s++;
    *(m_frameBuff++) = paramsValue;
  }
}

std::uint8_t Vga::getParamsValue(const LineParams& params)
{
  return params.blinking << 7 |
         static_cast<std::uint8_t>(params.bgcolor) << 4 |
         params.bright << 3 |
         static_cast<std::uint8_t>(params.fgcolor);
}
