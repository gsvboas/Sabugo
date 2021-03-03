#ifndef GRAPHICAL_CONTEXT_H_
#define GRAPHICAL_CONTEXT_H_

#include "Public/Math.h"
#include "Renderer/CPUdata.h"

void initGraphicalContext();
void prepareGraphicalContext();
void relinquishRenderData(const Vertex* const vertices, unsigned int vcount, DataLayout layout, unsigned int* indexes, unsigned int icount);
void drawContextData(unsigned int icount, Primitive mode);
void graphicalContextTerminate();
#endif

