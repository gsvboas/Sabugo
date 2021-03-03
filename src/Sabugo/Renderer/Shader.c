#include "Shader.h"
#include "ShaderGLSL.h"
#include "Public/ShaderType.h"
#include "Extra/CExtend.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Shader
{
    char* vs_path;
    char* fs_path;

    char* vs_src;
    char* fs_src;
    unsigned int program;
} Shader;

Shader SHADER;
static const char* const DEFAULT_VERTEX_SHADER = "res/shaders/vertex";
static const char* const DEFAULT_FRAGMENT_SHADER = "res/shaders/fragment";

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


void shaderCleanup()
{
    if (SHADER.vs_path)
	free(SHADER.vs_path);
    if (SHADER.fs_path)
	free(SHADER.fs_path);
    if(SHADER.vs_src)
	free(SHADER.vs_src);
    if (SHADER.fs_src)
	free(SHADER.fs_src);
    if (SHADER.program)
	glslDeleteShadingProgram(SHADER.program);
}

void setDefaultShaders()
{
    size_t vs_len, fs_len;
    shaderCleanup();

    vs_len = strlen(DEFAULT_VERTEX_SHADER);
    fs_len = strlen(DEFAULT_FRAGMENT_SHADER);

    SHADER.vs_path = (char*)mallocSafe((vs_len + 1) * sizeof(char));
    SHADER.fs_path = (char*)mallocSafe((fs_len + 1) * sizeof(char));
    if (!SHADER.vs_path || !SHADER.fs_path)
	return;

    strcpy(SHADER.vs_path, DEFAULT_VERTEX_SHADER);
    strcpy(SHADER.fs_path, DEFAULT_FRAGMENT_SHADER);

    SHADER.vs_src = shaderSourceStringFromFile(SHADER.vs_path);
    SHADER.fs_src = shaderSourceStringFromFile(SHADER.fs_path);
    SHADER.program = glslCreateShadingProgram(SHADER.vs_src, SHADER.fs_src);
}

void setCustomShader(const char* const path, ShaderType type)
{
    size_t len = strlen(path);

    if (SHADER.program)
	glslDeleteShadingProgram(SHADER.program);
    if (!SHADER.vs_path || !SHADER.fs_path || !SHADER.vs_src || !SHADER.fs_src)
	setDefaultShaders();

    switch (type)
    {
	case VERTEX_SHADER:
	    if (SHADER.vs_path)
		free(SHADER.vs_path);
	    if (SHADER.vs_src)
		free(SHADER.vs_src);
	    SHADER.vs_path = (char*)mallocSafe((len + 1) * sizeof(char));
	    strcpy(SHADER.vs_path, path);
	    SHADER.vs_src = shaderSourceStringFromFile(SHADER.vs_path);
	    break;
	case FRAGMENT_SHADER:
	    if (SHADER.fs_path)
		free(SHADER.fs_path);
	    if (SHADER.fs_src)
		free(SHADER.fs_src);
	    SHADER.fs_path = (char*)mallocSafe((len + 1) * sizeof(char));
	    strcpy(SHADER.fs_path, path);
	    SHADER.fs_src = shaderSourceStringFromFile(SHADER.fs_path);
	    break;
	default:
	    break;
    }
    SHADER.program = glslCreateShadingProgram(SHADER.vs_src, SHADER.fs_src);
}

unsigned int getActiveShader()
{
    return SHADER.program;
}

void createShader()
{
    setDefaultShaders();
}

void shaderTerminate()
{
    shaderCleanup();
}

