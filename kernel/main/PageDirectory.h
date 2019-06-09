#pragma once

#pragma pack(push, 1)

class PageDirectory
{
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

public:
  PageDirectory()
  {

  }

private:
  Entry m_entry;
}

#pragma pack(pop)
