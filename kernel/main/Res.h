#pragma once

#include <io/Ata.h>
#include <io/Vga.h>

class Res
{
public:
  static Ata& getAta() { return *m_ata; }
  static void setAta(Ata& ata) { m_ata = &ata; }
  static Vga& getVga() { return *m_vga; }
  static void setVga(Vga& vga) { m_vga = &vga; }
  static bool run;

private:
  static Vga* m_vga;
  static Ata* m_ata;
};
