#include "Memory.h"

#include "Res.h"
#include "System.h"

void Memory::init()
{
  using std::size_t;

  const size_t kernelPageDirBufAddr =
    reinterpret_cast<std::size_t>(m_kernelPageDirBuf);

  constexpr size_t align = PageDirectory::getAlign();
  const size_t shift = align - (kernelPageDirBufAddr % align) % align;
  m_kernelPageDir = reinterpret_cast<PageDirectory*>(m_kernelPageDirBuf + shift);

  // just in case
  const bool isAligned = reinterpret_cast<size_t>(m_kernelPageDir) % align == 0;
  const bool isFitted =
    m_kernelPageDir <= reinterpret_cast<PageDirectory*>(m_kernelPageDirBuf + align);
  if (!isAligned || !isFitted)
  {
    Res::getVga().print("KERNEL PANIC! Invalid kernel Page Directory address!");
    System::halt();
  } 

  // the constructor has never been called
  *m_kernelPageDir = PageDirectory();
}
