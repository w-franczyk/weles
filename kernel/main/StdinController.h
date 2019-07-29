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
  bool m_bufferWholeLine = false;
  char* m_targetBuf = nullptr;
  std::size_t m_targetBufPos = 0;
};
