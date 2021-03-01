#include "Sabugo.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* const NAME = "SABUGO WINDOW";

int main()
{
    createWindow(WIDTH, HEIGHT, NAME);

    while (windowIsOpen())
    {
	display();
    }
    return 0;
}

