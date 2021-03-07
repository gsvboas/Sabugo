#ifndef SABUGO_H_
#define SABUGO_H_

#include "sabugo/public/Color.h"

void createWindow(int width, int height, const char* const name);
void display();
void terminate();
int windowIsOpen();

void setBackgroundColor(Color color);

#endif
