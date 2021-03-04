/* ************************************ * START OF FILE * ************************************* */
/* */
/* */
/* */
/* *********************************** * GLOBAL INCLUDES * ************************************ */
#include "Sabugo.h"
#include "Debug/Debug.h"
#include "Core/Log.h"
#include "Public/Math.h"
#include "Renderer/Renderer.h"

#include <stdio.h>
#include <math.h>

#ifdef GL_BACKEND
/* ***************************** * START OF GL IMPLEMENTATION * ******************************* */
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */
/* **************************** * PRIVATE FUNCTIONS DEFINITIONS * ***************************** */
/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
const float PI = 3.14159265;

void drawFillRectangle(Vec2f nw, Vec2f dim, Color color)
{
    Vec2f ne, se, sw;
    Vec3ui index;

    ne.x = nw.x + dim.x;
    ne.y = nw.y;

    se.x = ne.x;
    se.y = ne.y + dim.y;

    sw.x = nw.x;
    sw.y = se.y;


    index = renderTriangle(nw, ne, sw, color);
    index.i = appendVertexToVertices(se, color);
    appendIndexToIndexes(index.i);
    appendIndexToIndexes(index.j);
    appendIndexToIndexes(index.k);

}
void drawFillTriangle(Vec2f a, Vec2f b, Vec2f c, Color color)
{
    renderTriangle(a, b, c, color);
}
void drawFillCircle(Vec2f center, float radius, Color color)
{
    drawFillCircleCustomDensity(center, radius, color, 36);
}
void drawFillCircleCustomDensity(Vec2f center, float radius, Color color, unsigned int density)
{
    Vec3ui index;
    Vec2f v1, v2;
    unsigned int i;

    index.i = appendVertexToVertices(center, color);

    v1.x = center.x;
    v1.y = center.y + radius;
    index.j = appendVertexToVertices(v1, color);
    for (i = 1; i < density + 1; i++)
    {
	v2.x = radius * sin((360.0f/density * i) * (PI/180.0f)) + center.x;
	v2.y = radius * cos((360.0f/density * i) * (PI/180.0f)) + center.y;
	printf("Iter %u: v2.x = %.3f, v2.y = %.3f\n", i, v2.x, v2.y);
	index.k = appendVertexToVertices(v2, color);

	appendIndexToIndexes(index.i);
	appendIndexToIndexes(index.j);
	appendIndexToIndexes(index.k);
	index.j = index.k;
    }

}

/* ************************************* * END OF FILE * ************************************** */
#endif

