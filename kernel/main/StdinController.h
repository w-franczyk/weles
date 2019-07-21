#pragma once

#include "ProcessController.h"

#include <cstdlib>

class StdinController
{
public:
  explicit StdinController(ProcessController& processController) :
    m_processController(processController) {}

  void getLine(char* target);
  void push(char c);

private:
  ProcessController& m_processController;
  char m_buffer[256] = {0};
  std::size_t m_bufferPos = 0;
  bool m_waitForWholeLine = false;
};
