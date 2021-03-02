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

#ifdef GL_BACKEND
/* ***************************** * START OF GL IMPLEMENTATION * ******************************* */
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */
/* **************************** * PRIVATE FUNCTIONS DEFINITIONS * ***************************** */
/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
void drawRectangle(Vec2f nw, Vec2f dim, Color color)
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
void drawTriangle(Vec2f a, Vec2f b, Vec2f c, Color color)
{
    renderTriangle(a, b, c, color);
}
/* ************************************* * END OF FILE * ************************************** */
#endif

