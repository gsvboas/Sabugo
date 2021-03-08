#include "Sabugo.h"

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const char* const WIN_NAME = "Demo Basic Lines and Curves";

int main()
{
    Vec2f v1, v2, v3;

    v1.x = +0.0f;
    v1.y = +0.5f * 1.73;

    v2.x = +0.5f;
    v2.y = +0.0f;

    v3.x = -0.5f;
    v3.y = +0.0f;

    createWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
    while (windowIsOpen())
    {
	drawFillTriangle(v1, v2, v3, RED);
	display();
    }
    return 0;
}

