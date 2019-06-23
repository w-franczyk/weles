#pragma once

#include <cstdlib>

template <class EntryType>
class PagingStructure
{
public:
  PagingStructure() = default;

  static constexpr std::size_t getAlign() { return m_align; }
  static constexpr std::size_t getBufferSize() { return sizeof(EntryType) * m_entriesCnt; }
  
  const std::uint8_t* getBuffer() const { return reinterpret_cast<const std::uint8_t*>(m_begin); }
  std::size_t getBufferAddr() const { return reinterpret_cast<std::size_t>(m_begin); }
  void setAlignedBuffer(std::uint8_t* buf)
  {
    m_begin = reinterpret_cast<EntryType*>(buf);
    for (std::size_t i = 0; i < m_entriesCnt; ++i)
      m_begin[i] = EntryType();

    m_end = m_begin + getBufferSize();
    m_ptr = m_begin;
  }

  void pushBack(const EntryType& entry)
  {
    *m_ptr = entry;
    ++m_ptr;
  }

protected:
  static constexpr std::size_t m_align = 4096;
  static constexpr std::size_t m_entriesCnt = 1024;

  // pointers to move through preallocated aligned buffer of size getBufferSize()
  EntryType* m_begin = nullptr;
  EntryType* m_end = nullptr;
  EntryType* m_ptr = nullptr;
};
