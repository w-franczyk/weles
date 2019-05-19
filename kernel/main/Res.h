#pragma once

class Vga;

class Res
{
public:
  static Vga& getVga() { return *m_vga; }
  static void setVga(Vga& vga) { m_vga = &vga; }
  static bool run;

private:
  static Vga* m_vga;
};
