#pragma once

#include <libk/cstdlib>

class Vga
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
    LightGrey,
    DarkGrey,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    LightBrown,
    White
  };
  
  enum IoPort : std::uint16_t
  {
    PortCommand = 0x3d4,
    PortData = 0x3d5
  };

  enum IoCommand : std::uint8_t
  {
    CmdMoveCursorHigh = 14,
    CmdMoveCursorLow = 15
  };

  struct LineParams
  {
    bool blinking = false;
    Color bgcolor = Color::Black;
    bool bright = false;
    Color fgcolor = Color::LightMagenta;
  };

  void print(const char* s);
  void print(const char* s, Color fgcolor);
  void print(const char* s, Color fgcolor, Color bgcolor);
  void print(const char* s, const LineParams& params);

private:
  std::uint8_t getParamsValue(const LineParams& params);

  std::uint8_t* m_frameBuff = reinterpret_cast<std::uint8_t*>(0xb8000);

  // default values
  const unsigned m_lines = 25;
  const unsigned m_columns = 80;
};
