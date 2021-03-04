#include "CExtend.h"
#include <stdio.h>
#include <stdlib.h>



void* mallocSafe(size_t sz)
{
    void* ptr = malloc(sz);
    if (ptr)
	return ptr;
    printf("MALLOCSAFE DETECTS CRASH\n");
    fflush(stdout);
    return NULL;
}

