#pragma once

#include <libk/cstdlib>
#include <main/Gdt.h>
#include <main/InterruptFrame.h>

class InterruptDescriptor
{
  enum class GateType : std::uint8_t
  {
    Task = 0x5,
    Interrupt = 0xe,
    Trap = 0xf
  };

#pragma pack(push, 1)
  struct Entry
  {
    std::uint16_t offsetLo = 0;
    std::uint16_t selector = Gdt::codeSegment;
    std::uint8_t reserved = 0;
    GateType gateType = GateType::Interrupt;
    std::uint16_t offsetHi = 0;
  };
#pragma pack(pop)

public:
  InterruptDescriptor(void(*isr)(InterruptFrame*))
  {
    const std::uint32_t isrAddress = reinterpret_cast<std::uint32_t>(isr); 
    m_entry.offsetLo = isrAddress & 0x0000ffff;
    m_entry.offsetHi = isrAddress >> 16;
  }

  std::uint64_t serialize() const
  {
    return *reinterpret_cast<const std::uint64_t*>(&m_entry);
  }

private:
  Entry m_entry;
};
