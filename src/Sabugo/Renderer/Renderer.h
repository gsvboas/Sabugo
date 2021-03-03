#ifndef RENDERER_H_
#define RENDERER_H_

#include "Public/Math.h"

unsigned int appendVertexToVertices();
void appendIndexToIndexes();
Vec3ui renderTriangle(Vec2f a, Vec2f b, Vec2f c, Color color);
void prepareRenderer();
void startRenderer(int winBufferWidth, int winBufferHeight);
void rendererConsolidateDrawCalls();
void rendererTerminate();
#endif

