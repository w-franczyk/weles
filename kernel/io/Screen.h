#pragma once

#include <libk/cstdlib>

class Screen
{
public:
  enum class Color : std::uint8_t
  {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    White,
    Grey,
    LightBlue,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    BrightWhite
  };

  struct LineParams
  {
    bool blinking = false;
    Color bgcolor = Color::Black;
    bool bright = false;
    Color fgcolor = Color::White;
  };

  void print(const char* s)
  {
    LineParams params;
    print(s, params);
  }

  void print(const char* s, Color fgcolor)
  {
    LineParams params;
    params.fgcolor = fgcolor;
    print(s, params);
  }

  void print(const char* s, Color fgcolor, Color bgcolor)
  {
    LineParams params;
    params.fgcolor = fgcolor;
    params.bgcolor = bgcolor;
    print(s, params);
  }

  void print(const char* s, const LineParams& params)
  {
    const std::uint8_t paramsValue = getParamsValue(params);
    while (*s != 0)
    {
      *(m_writeBuff++) = *s++;
      *(m_writeBuff++) = paramsValue;
    }
  }

private:
  std::uint8_t getParamsValue(const LineParams& params)
  {
    return params.blinking << 7 |
           static_cast<std::uint8_t>(params.bgcolor) << 4 |
           params.bright << 3 |
           static_cast<std::uint8_t>(params.fgcolor);
  }

  std::uint8_t* m_writeBuff = reinterpret_cast<std::uint8_t*>(0xb8000);

  // default values
  const unsigned m_lines = 25;
  const unsigned m_columns = 80;
};
