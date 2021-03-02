/* *********************************** * GLOBAL INCLUDES * ************************************ */
/* *********************************** * GLOBAL INCLUDES * ************************************ */
#include "Sabugo.h"
#include "Public/Math.h"
#include "Renderer/Renderer.h"
#include "Renderer/GraphicalContextGL.h"
#include "Renderer/CPUdata.h"
#include <stdio.h>
#include <stdlib.h>


/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
#define VERTICES_MAX_BUFFER 2000
#define INDEXES_MAX_BUFFER 2000



typedef struct RenderDataCPU
{
    /* CPU data buffers */
    Vertex vertices[VERTICES_MAX_BUFFER];
    unsigned int vertices_count;

    unsigned int indexes[INDEXES_MAX_BUFFER];
    unsigned int indexes_count;

    DataLayout layout;


} RenderData;

RenderData RENDERER;

/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */

/* ***************************** * PRIVATE FUNCTION DEFINITIONS * ***************************** */

/* ********************** * SEMI PUBLIC INTERFACE FUNCTION DEFINITIONS * ********************** */
void startRenderer(int winBufferWidth, int winBufferHeight)
{
    RENDERER.layout.attributes_count = 2;
    RENDERER.layout.attributes = (Attribute*)malloc(RENDERER.layout.attributes_count * sizeof(Attribute));

    /* DEFINE LAYOUT */
    RENDERER.layout.attributes[0].type = FLOAT;
    RENDERER.layout.attributes[0].offset = 0;
    RENDERER.layout.attributes[0].length = 2;
    RENDERER.layout.attributes[1].type = FLOAT;
    RENDERER.layout.attributes[1].offset = 2 * sizeof(float);
    RENDERER.layout.attributes[1].length = 4;


    RENDERER.vertices_count = 0;
    RENDERER.indexes_count = 0;
    initGraphicalContext(winBufferWidth, winBufferHeight);
}

void prepareRenderer()
{
    RENDERER.vertices_count = 0;
    RENDERER.indexes_count = 0;
    prepareGraphicalContext();
}

unsigned int appendVertexToVertices(Vec2f v, Color color)
{
    printf("Appending v.x = %.3f, v.y = %.3f to vertices\n", v.x, v.y);
    RENDERER.vertices[RENDERER.vertices_count].pos[0] = v.x;
    RENDERER.vertices[RENDERER.vertices_count].pos[1] = v.y;
    RENDERER.vertices[RENDERER.vertices_count].color[0] = color.r;
    RENDERER.vertices[RENDERER.vertices_count].color[1] = color.g;
    RENDERER.vertices[RENDERER.vertices_count].color[2] = color.b;
    RENDERER.vertices[RENDERER.vertices_count].color[3] = color.a;

    /*printf("v no. %u data: pos[0] = %.3f, pos[1] = %.3f\n", RENDERER.vertices_count, RENDERER.vertices[RENDERER.vertices_count].pos[0], RENDERER.vertices[RENDERER.vertices_count].pos[1]);*/
    RENDERER.vertices_count++;
    return RENDERER.vertices_count - 1;
}

Vec3ui renderTriangle(Vec2f a, Vec2f b, Vec2f c, Color color)
{
    Vec3ui index;
    index.i = appendVertexToVertices(a, color);
    appendIndexToIndexes(index.i);

    index.j = appendVertexToVertices(b, color);
    appendIndexToIndexes(index.j);

    index.k = appendVertexToVertices(c, color);
    appendIndexToIndexes(index.k);

    return index;
}

void appendIndexToIndexes(unsigned int index)
{
    printf("Appending index i = %u\n", index);
    RENDERER.indexes[RENDERER.indexes_count] = index;
    RENDERER.indexes_count++;
}

void rendererConsolidateDrawCalls()
{
    unsigned int i, j;

    printf("Indexes count is %u. Indexes:\n", RENDERER.indexes_count);
    for (i = 0; i < RENDERER.indexes_count; i++)
    {
	printf("%u ", RENDERER.indexes[i]);
    }
    printf("\n");
    relinquishRenderData(RENDERER.vertices, RENDERER.vertices_count, RENDERER.layout, RENDERER.indexes, RENDERER.indexes_count);
    drawContextData(RENDERER.indexes_count, TRIANGLES);
}
/* ************************ * PUBLIC INTERFACE FUNCTION DEFINITIONS * ************************* */

/* ************************************* * END OF FILE * ************************************** */

