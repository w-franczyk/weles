#include <stdio.h>
 
#if defined(WELES_KERNEL)
#include "CVga.h"
#endif
 
int putchar(int ic) {
#if defined(WELES_KERNEL)
    char c = (char) ic;
    vgaPrint(c);
#else
    // TODO: Implement stdio and the write system call.
#endif
    return ic;
}
