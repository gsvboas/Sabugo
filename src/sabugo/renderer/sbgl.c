#define GLEW_STATIC

#include "sabugo/Sabugo.h"

#include "vendor/GL/glew.h"


void sbglInitGraphicsContext(int x, int y, int width, int height)
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
	return;
    }

    glViewport(x, y, width, height);
}

void sbglClear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
