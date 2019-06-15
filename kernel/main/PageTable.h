#pragma once

#include "PagingStructure.h"

#include <libk/cstdlib>

#pragma pack(push, 1)
class PageDescriptor
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
  PageDescriptor() :
    m_pageAddr(0),
    unused1(0),
    m_global(0),
    unused2(0),
    m_dirty(0),
    m_accessed(0),
    m_cacheDisabled(0),
    m_writeThrough(0),
    m_accessLevel(AccessSupervisor),
    m_permission(ReadWrite),
    m_present(0)
  {
    static_assert(sizeof(*this) == 4);
  }

  void setAddress(std::size_t address) { m_pageAddr = address; }
  void setDirty() { m_dirty = 1; }
  void setReadOnly() { m_permission = ReadOnly; }
  void setReadWrite() { m_permission = ReadWrite; }
  void setUser() { m_accessLevel = AccessUser; }
  void setSupervisor() { m_accessLevel = AccessSupervisor; }
  void setPresent() { m_present = 1; }

private:
  std::uint32_t m_pageAddr : 20;
  std::uint32_t unused1 : 3;
  std::uint32_t m_global : 1;
  std::uint32_t unused2 : 1;
  std::uint32_t m_dirty : 1;
  std::uint32_t m_accessed : 1;
  std::uint32_t m_cacheDisabled : 1;
  std::uint32_t m_writeThrough : 1;
  std::uint32_t m_accessLevel : 1;
  std::uint32_t m_permission : 1;
  std::uint32_t m_present : 1;
};
#pragma pack(pop)

using PageTable = PagingStructure<PageDescriptor>;
