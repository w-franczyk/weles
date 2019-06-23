#include "Ps2Keyboard.h"

#include "Pic.h"
#include "PortIo.h"

#include <cstdlib>

void Ps2Keyboard::processEvent()
{
  constexpr std::uint8_t keyboardPort = 0x60;
  std::uint8_t scancode = inb(keyboardPort);
  outb(Pic::Pic1PortCmd, Pic::PicCmdAck);

  // StdinController::Action action = scancodeToStdinAction(scancode);
  m_stdinController.push(scancode);
}
