#pragma once

namespace System
{

extern "C"
{
  void enablePaging(const std::uint8_t* pageDirectory);
  void halt();
}

} // namespace System
