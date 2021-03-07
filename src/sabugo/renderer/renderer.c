#include "sabugo/Sabugo.h"
#include "vendor/GL/glew.h"

#include "sabugo/renderer/sbgl.h"
#include "sabugo/public/Color.h"

void initRenderer(int bufferWidth, int bufferHeight)
{
    sbglInitGraphicsContext(0, 0, bufferWidth, bufferHeight);
}

void setBackgroundColor(Color color)
{
    sbglClear(color);
}
