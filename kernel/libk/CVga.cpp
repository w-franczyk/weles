#include <main/Res.h>

extern "C"
{
  
void vgaPrint(const char* c)
{
  Res::getVga().print(c);
}

}
