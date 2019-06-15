#pragma once

#include "PagingStructure.h"

#include <libk/cstdlib>

#pragma pack(push, 1)
class PageTableDescriptor
{
  enum AccessLevel
  {
    AccessSupervisor = 0,
    AccessUser = 1
  };

  enum Permission
  {
    ReadOnly = 0,
    ReadWrite = 1
  };

public:
  PageTableDescriptor() :
    m_pageTableAddr(0),
    unused1(0),
    unused2(0),
    m_pageSize(0),
    unused3(0),
    m_accessed(0),
    m_cacheDisabled(0),
    m_writeThrough(0),
    m_accessLevel(AccessSupervisor),
    m_permission(ReadWrite),
    m_present(0)
  {
    static_assert(sizeof(*this) == 4);
  }

  void setAddress(std::size_t address) { m_pageTableAddr = address >> 12; }
  void setPresent() { m_present = 1; }
  void setReadOnly() { m_permission = ReadOnly; }
  void setReadWrite() { m_permission = ReadWrite; }
  void setUser() { m_accessLevel = AccessUser; }
  void setSupervisor() { m_accessLevel = AccessSupervisor; }

private:
  std::uint32_t m_pageTableAddr : 20;
  std::uint32_t unused1 : 3;
  std::uint32_t unused2 : 1;
  std::uint32_t m_pageSize : 1;
  std::uint32_t unused3 : 1;
  std::uint32_t m_accessed : 1;
  std::uint32_t m_cacheDisabled : 1;
  std::uint32_t m_writeThrough : 1;
  std::uint32_t m_accessLevel : 1;
  std::uint32_t m_permission : 1;
  std::uint32_t m_present : 1;
};
#pragma pack(pop)

using PageDirectory = PagingStructure<PageTableDescriptor>;
