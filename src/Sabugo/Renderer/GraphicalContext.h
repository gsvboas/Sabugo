#ifndef GRAPHICAL_CONTEXT_H_
#define GRAPHICAL_CONTEXT_H_

#include "Public/Math.h"

void initGraphicalContext();
void consolidateDrawCalls();

unsigned int appendVertexToVertices(Vec2f v, Color color);
void appendIndexToIndexes(unsigned int index);
Vec3ui renderTriangle(Vec2f a, Vec2f b, Vec2f c, Color color);

#endif

