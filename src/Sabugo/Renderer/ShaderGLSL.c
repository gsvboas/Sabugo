#include "ShaderGLSL.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int compileShader(const char* const src, unsigned int type)
{
    unsigned int id;
    int compileStatus, infoLogLength;
    char* infoLogMessage;

    id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE){
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	infoLogMessage = (char*)malloc((infoLogLength + 1) * sizeof(char));
	if (!infoLogMessage)
	    return 0;

	infoLogMessage[infoLogLength] = '\0';
	glGetShaderInfoLog(id, infoLogLength, &infoLogLength, infoLogMessage);
	printf("GLSL Compilation error at %s shader.\nError output:\n%s\n", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", infoLogMessage);
	fflush(stdout);
	free(infoLogMessage);
	id = 0;
    }
    return id;

}

unsigned int glslCreateShadingProgram(const char* const vertex, const char* const fragment)
{
    unsigned int program;
    unsigned int vs, fs;

    printf("Vertex:\n%s\nFragment:\n%s\n", vertex, fragment);
    program = glCreateProgram();
    vs = compileShader(vertex, GL_VERTEX_SHADER);
    fs = compileShader(fragment, GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    return program;
}

void glslDeleteShadingProgram(unsigned int program)
{
    glDeleteProgram(program);
}

