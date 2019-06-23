#pragma once

#include "PageDirectory.h"
#include "PageTable.h"

#include <cstdlib>

class Memory
{
public:
  Memory() = default;
  void init();

private:
  static constexpr unsigned m_pageSize = 4096;

  PageDirectory m_kernelPageDir;
  PageTable m_kernelPageTable;
  std::uint8_t m_kernelPagingBuf[
    PageDirectory::getAlign() +
    PageDirectory::getBufferSize() + 
    PageTable::getBufferSize()
  ];
};
