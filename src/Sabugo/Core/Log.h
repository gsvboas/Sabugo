#ifndef LOG_H_
#define LOG_H_

#include "Debug/Debug.h"

void logBegin(SABUGO_ERROR err);
void logEnd();
void logStr(const char* const str);

#endif

