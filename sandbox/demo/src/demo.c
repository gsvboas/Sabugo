#include "Sabugo.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* const NAME = "SABUGO WINDOW";

int main()
{
    Vec2f v1, v2, v3;
    Vec2f v4, v5;
    float incr = 0.01f;
    createWindow(WIDTH, HEIGHT, NAME);

    v1.x = +0.0f;
    v1.y = -0.5f;

    v2.x = -0.5f;
    v2.y = +0.5f;

    v3.x = +0.5f;
    v3.y = +0.5f;

    v4.x = +1.0f;
    v4.y = +1.0f;

    v5.x = -0.1f;
    v5.y = -0.1f;

    while (windowIsOpen())
    {
	incr = v4.x >= 1.0f ? -0.01f : v4.x <= -1.0f ? 0.01f : incr;
	v4.x += incr;
	drawRectangle(v4, v5, RED);
	drawTriangle(v1, v2, v3, RED);
	display();
    }
    return 0;
}

