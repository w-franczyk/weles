#include <main/Res.h>

extern "C"
{
  
void vgaPrint(char c)
{
  Res::getVga().print(c);
}

}
