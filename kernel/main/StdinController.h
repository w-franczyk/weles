#pragma once

#include "ProcessController.h"

#include <cstdlib>

class StdinController
{
public:
  explicit StdinController(ProcessController& processController) :
    m_processController(processController) {}

  void push(char c)
  {
    m_processController.stdin(&c, 1);
  }

private:
  ProcessController& m_processController;
  std::uint8_t buffer[256];
};
