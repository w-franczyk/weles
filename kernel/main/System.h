#pragma once

#include "PageDirectory.h"

namespace System
{

extern "C"
{
  void enablePaging(const PageDirectory* pageDirectory);
  void halt();
}

} // namespace System
