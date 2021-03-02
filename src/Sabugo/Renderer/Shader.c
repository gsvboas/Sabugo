#include "Shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

char* shaderSourceStringFromFile(const char* const path)
{
    char* shaderSourceString;
    FILE* shaderFile;
    int shaderSourceLength;

    shaderFile = fopen(path, "rb");
    if (!shaderFile)
	return NULL;

    fseek(shaderFile, 0, SEEK_END);
    shaderSourceLength = ftell(shaderFile);
    rewind(shaderFile);

    shaderSourceString = (char*)malloc((shaderSourceLength + 1) * sizeof(char));
    if (!shaderSourceString){
	fclose(shaderFile);
	return NULL;
    }

    shaderSourceString[shaderSourceLength] = '\0';
    fread(shaderSourceString, sizeof(char), shaderSourceLength, shaderFile);
    fclose(shaderFile);

    return shaderSourceString;
}

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
unsigned int createShadingProgram(const char* const vertex, const char* const fragment)
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

