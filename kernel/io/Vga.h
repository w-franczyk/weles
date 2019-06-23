#pragma once

#include <cstdlib>

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
    PortVgaResource = 0x3d4,
    PortVgaData = 0x3d5
  };

  enum IoResource : std::uint8_t
  {
    ResCursorPosHigh = 14,
    ResCursorPosLow = 15
  };

  struct LineParams
  {
    bool blinking = false;
    Color bgcolor = Color::Black;
    bool bright = false;
    Color fgcolor = Color::LightGrey;
  };

  Vga();
  void initCursorPos();
  std::uint16_t getCursorPos() const;
  void print(const char* s);
  void print(const char* s, Color fgcolor);
  void print(const char* s, Color fgcolor, Color bgcolor);
  void print(const char* s, const LineParams& params);
  void poll() const;

private:
  void addLine();
  std::uint8_t getParamsValue(const LineParams& params) const;

  std::uint8_t* m_framePtr = nullptr;
  std::uint16_t m_cursorPos = 0;

  // default values
  std::uint8_t* const m_frameBuffer = reinterpret_cast<std::uint8_t*>(0xb8000);
  const unsigned m_lines = 25;
  const unsigned m_columns = 80;
};
