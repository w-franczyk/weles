#pragma once

#include <libk/cstdlib>


class PageDirectory
{
#pragma pack(push, 1)
  struct Entry
  {
    std::uint32_t pageTableAddr : 20;
    std::uint32_t dummy : 3;
    std::uint32_t : 1;
    std::uint32_t pageSize : 1;
    std::uint32_t : 1;
    std::uint32_t accessed : 1;
    std::uint32_t cacheDisabled : 1;
    std::uint32_t writeThrough : 1;
    std::uint32_t accessLevel : 1;
    std::uint32_t readWrite : 1;
    std::uint32_t present : 1;
  };
#pragma pack(pop)

public:
  PageDirectory()
  {
    static_assert(sizeof(Entry) == 4, "Incorrect size of PageDirectory::Entry");
    static_assert(sizeof(*this) == sizeof(Entry) * 1024, "Incorrect size of PageDirectory");
  }

  static constexpr std::size_t getAlign() { return m_align; }

//  void addPageTable(

private:
  static constexpr std::size_t m_align = 4096;
  Entry m_entry[1024];
};
