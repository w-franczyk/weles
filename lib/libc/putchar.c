#include <stdio.h>
 
#if defined(WELES_KERNEL)
#include "CVga.h"
#else
#include <sys/syscall.h>
#endif
 
int putchar(int ic) {
    char c = (char) ic;
#if defined(WELES_KERNEL)
    vgaPrint(c);
#else
    sysPutchar(c);
#endif
    return ic;
}
