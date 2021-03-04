#include "Sabugo.h"
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* const NAME = "SABUGO WINDOW";




void demofoo(Vec2f* v, float* incr);
int main()
{
    Vec2f v;
    /* 2 Tri */
    Vec2f v1, v2, v3;
    Vec2f v4, v5, v6;
    /* Rec */
    Vec2f v7, v8;

    /* Two Circles */

    v7.x = -0.15f;
    v7.y = +0.165f;

    v8.x = -1.9 * v7.x;
    v8.y = -0.7f;


    v1.x = -0.35f;
    v1.y = -0.255f;

    v2.x = +0.05f;
    v2.y = -0.75f;

    v3.x = -0.175f;
    v3.y = +0.175f;

    v4.x = +0.35f;
    v4.y = -0.255f;

    v5.x = -0.05f;
    v5.y = -0.75f;

    v6.x = +0.175f;
    v6.y = +0.175f;

    v.x = +0.9f;
    v.y = +0.9f;
    createWindow(WIDTH, HEIGHT, NAME);
    while (windowIsOpen())
    {
	/* demofoo(&v, &incr); */
	drawFillRectangle(v7, v8, YELLOW);
	drawFillTriangle(v1, v2, v3, DARK_GREEN);
	drawFillTriangle(v4, v5, v6, DARK_GREEN);


	display();
    }
    return 0;
}

void demofoo(Vec2f* v, float* incr)
{
    Vec2f v1, v2, v3;
    Vec2f v5, v6;

    v1.x = +0.0f;
    v1.y = -0.175f;

    v2.x = +0.0f;
    v2.y = +0.5f;

    v3.x = +0.5f;
    v3.y = +0.5f;

    v5.x = +0.1f;
    v5.y = +0.1f;

    v6.x = +0.7f;
    v6.y = +0.7f;
    *incr = v->x > 1.0f ? -0.01f : v->x < -1.0f ? 0.01f : *incr;
    printf("%.3f\n", *incr);
    v->x += *incr;
    drawFillRectangle(*v, v5, RED);
    drawFillTriangle(v1, v2, v3, BLUE);
    drawFillCircle(v6, 0.1f, GREEN);
}

