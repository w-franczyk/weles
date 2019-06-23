#pragma once

#include "ProcessController.h"

#include <cstdlib>

class StdinController
{
public:
  struct Action {};

  explicit StdinController(ProcessController& processController) :
    m_processController(processController) {}

  void push(const Action& /*action*/)
  {
    m_processController.stdin(buffer, 1);
  }

private:
  ProcessController& m_processController;
  std::uint8_t buffer[256];
};
