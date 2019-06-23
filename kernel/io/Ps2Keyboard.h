#pragma once

#include <main/StdinController.h>

#include <cstdlib>

class Ps2Keyboard
{
public:
  explicit Ps2Keyboard(StdinController& c) : m_stdinController(c) {}

  void processEvent();

private:
  StdinController::Action scancodeToStdinAction(std::uint8_t scancode);

  bool m_capsLock = false;
  StdinController& m_stdinController;
};
