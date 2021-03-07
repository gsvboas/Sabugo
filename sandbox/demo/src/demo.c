#include "sabugo/Sabugo.h"


int main()
{
    createWindow(800, 600, "Sabugo Window");

    while (windowIsOpen())
    {
	setBackgroundColor(RED);
	display();
    }

    terminate();
    return 0;
}
