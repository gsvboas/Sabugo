#include "Sabugo.h"
#include "Renderer/Renderer.h"

void drawLine(Vec2f a, Vec2f b, float thickness, Color color)
{
    appendVertexToVertices(a, color);
    appendVertexToVertices(b, color);

}

