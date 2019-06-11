#pragma once

#include "PageDirectory.h"

#include <libk/cstdlib>

class Memory
{
#pragma pack(push, 1)

  struct PageTableEntry
  {
    std::uint32_t pageAddr : 20;
    std::uint32_t dummy : 3;
    std::uint32_t global : 1;
    std::uint32_t : 1;
    std::uint32_t dirty : 1;
    std::uint32_t accessed : 1;
    std::uint32_t cacheDisabled : 1;
    std::uint32_t writeThrough : 1;
    std::uint32_t accessLevel : 1;
    std::uint32_t readWrite : 1;
    std::uint32_t present : 1;
  };
#pragma pack(pop)

public:
  Memory() = default;
  void init();

private:
  std::uint8_t m_kernelPageDirBuf[sizeof(PageDirectory) + PageDirectory::getAlign()];
  PageDirectory* m_kernelPageDir = nullptr;
};
