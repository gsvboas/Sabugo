#ifndef SHADER_H_
#define SHADER_H_

static const char* const DEFAULT_VERTEX_SHADER = "res/shaders/vertex";
static const char* const DEFAULT_FRAGMENT_SHADER = "res/shaders/fragment";

char* shaderSourceStringFromFile(const char* const path);
unsigned int createShadingProgram(const char* const vertex, const char* const fragment);

#endif

