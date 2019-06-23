#pragma once

#include <io/Ata.h>
#include <io/Ps2Keyboard.h>
#include <io/Vga.h>

class Res
{
public:
  static Ata& getAta() { return *m_ata; }
  static void setAta(Ata& ata) { m_ata = &ata; }
  static Ps2Keyboard& getKeyboard() { return *m_keyboard; }
  static void setKeyboard(Ps2Keyboard& keyboard) { m_keyboard = &keyboard; }
  static Vga& getVga() { return *m_vga; }
  static void setVga(Vga& vga) { m_vga = &vga; }
  static bool run;

private:
  static Ata* m_ata;
  static Ps2Keyboard* m_keyboard;
  static Vga* m_vga;
};
