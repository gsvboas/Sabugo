#ifndef SHADER_GLSL_H_
#define SHADER_GLSL_H_

void glslDeleteShadingProgram();
unsigned int glslCreateShadingProgram(const char* const vertex, const char* const fragment);

#endif

