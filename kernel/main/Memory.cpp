#include "Memory.h"

#include "Res.h"
#include "System.h"

void Memory::init()
{
  using std::size_t;

  const size_t pagingBufAddr = reinterpret_cast<std::size_t>(m_kernelPagingBuf);
  constexpr size_t align = PageDirectory::getAlign();
  const size_t shift = align - (pagingBufAddr % align) % align;
  std::uint8_t* pageDirBuf = m_kernelPagingBuf + shift;
  m_kernelPageDir.setAlignedBuffer(pageDirBuf);
  
  // just in case
  const bool isAligned = m_kernelPageDir.getBufferAddr() % align == 0;
  const bool isFitted = pageDirBuf <= m_kernelPagingBuf + align;
  if (!isAligned || !isFitted)
  {
    Res::getVga().print("KERNEL PANIC! Invalid kernel Page Directory address!");
    System::halt();
  } 

  m_kernelPageTable.setAlignedBuffer(pageDirBuf + PageDirectory::getBufferSize());
  PageTableDescriptor pageTableDesc;
  pageTableDesc.setReadWrite();
  pageTableDesc.setSupervisor();
  pageTableDesc.setPresent();
  pageTableDesc.setAddress(m_kernelPageTable.getBufferAddr());
  m_kernelPageDir.pushBack(pageTableDesc);

  // first 1024 pages (4MB) for the kernel
  // probably it will need to be extended
  PageDescriptor page;
  page.setReadWrite();
  page.setSupervisor();
  page.setPresent();
  for (size_t i = 0; i < 1024; ++i)
  {
    page.setAddress(i * m_pageSize);
    m_kernelPageTable.pushBack(page);
  }

  System::enablePaging(m_kernelPageDir.getBuffer());  
}
