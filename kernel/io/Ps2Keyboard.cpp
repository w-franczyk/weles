#include "Ps2Keyboard.h"

#include "Pic.h"
#include "PortIo.h"

#include <main/Key.h>

#include <cstdlib>

void Ps2Keyboard::processEvent()
{
  constexpr std::uint8_t keyboardPort = 0x60;
  std::uint8_t scancode = inb(keyboardPort);
  outb(Pic::Pic1PortCmd, Pic::PicCmdAck);

  constexpr unsigned char mapping[] = {
    0, Key::Escape, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    Key::Backspace, '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
    ']', '\n', Key::LeftCtrl, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', Key::LeftShift, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',
    '/', Key::RightShift, '*', Key::LeftAlt, ' ', Key::CapsLock}; 

  // only "Pressed" events mapped for now, "Released" ignored
  if (scancode < sizeof(mapping))
    m_stdinController.push(mapping[scancode]);
}
