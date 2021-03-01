#include "Log.h"
#include "Debug/Debug.h"
#include <stdio.h>

void logBegin(SABUGO_ERROR err)
{
    if (err != NO_ERROR)
	printf("[LOG]: ");
    else
	printf("[ERROR]: ");
    return;
}

void logEnd()
{
    printf("\n");
}

void logStr(const char* const str)
{
    printf(str);
}

