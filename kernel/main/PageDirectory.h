#pragma once

#include "PagingStructure.h"

#include <libk/cstdlib>

#pragma pack(push, 1)
class PageTableDescriptor
{
  enum Bits
  {
    BitPresent        = 0b00000001,
    BitReadWrite      = 0b00000010,
    BitUserSupervisor = 0b00000100,
    BitWriteThrough   = 0b00001000,
    BitCacheDisable   = 0b00010000,
    BitAccessed       = 0b00100000,
    BitPageSize       = 0b10000000
  };

public:
  PageTableDescriptor()
  {
    setReadWrite();
    static_assert(sizeof(*this) == 4);
  }

  void setAddress(std::size_t address)
  {
    m_descriptor = (address & 0xfffff000) | (m_descriptor & 0x00000fff);
  }
  void setPresent() { m_descriptor |= BitPresent; }
  void setReadOnly() { m_descriptor &= ~BitReadWrite; }
  void setReadWrite() { m_descriptor |= BitReadWrite; }
  void setUser() { m_descriptor |= BitUserSupervisor; }
  void setSupervisor() { m_descriptor &= ~BitUserSupervisor; }

private:
  std::uint32_t m_descriptor = 0;
};
#pragma pack(pop)

using PageDirectory = PagingStructure<PageTableDescriptor>;
