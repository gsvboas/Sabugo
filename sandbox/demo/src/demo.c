#include "Sabugo.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* const NAME = "SABUGO WINDOW";

int main()
{
    Vec2f v1, v2, v3;
    Vec2f v4, v5, v6;
    float incr = 0.01f;
    createWindow(WIDTH, HEIGHT, NAME);

    v1.x = +0.0f;
    v1.y = -0.5f;

    v2.x = -0.5f;
    v2.y = +0.5f;

    v3.x = +0.5f;
    v3.y = +0.5f;

    v4.x = +0.9f;
    v4.y = +0.9f;

    v5.x = +0.1f;
    v5.y = +0.1f;

    v6.x = +0.7f;
    v6.y = +0.7f;


    while (windowIsOpen())
    {
	incr = v4.x >= 1.0f ? -0.01f : v4.x <= -1.0f ? 0.01f : incr;
	v4.x += incr;
	drawFillRectangle(v4, v5, RED);
	drawFillTriangle(v1, v2, v3, BLUE);
	drawFillCircle(v6, 0.1f, GREEN);

	display();
    }
    return 0;
}

