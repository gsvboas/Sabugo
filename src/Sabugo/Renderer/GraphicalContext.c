/* ************************************ * START OF FILE * ************************************* */
/* */
/* */
/* */
/* *********************************** * GLOBAL INCLUDES * ************************************ */
#include "Sabugo.h"
#include "Debug/Debug.h"
#include "Core/Log.h"
#include "Renderer/GraphicalContext.h"
#include "Renderer/Shader.h"
#include "Renderer/CPUdata.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef GL_BACKEND
/* ***************************** * START OF GL IMPLEMENTATION * ******************************* */
#include <GL/glew.h>
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
#define MAX_VAOS 1
#define MAX_GPU_BUFFERS 1
typedef struct GraphicalContext
{
    /* OpenGL id's */
    unsigned int vaos[MAX_VAOS];
    unsigned int vbos[MAX_GPU_BUFFERS];
    unsigned int ibos[MAX_GPU_BUFFERS];

    unsigned int vaos_in_use;
    unsigned int vbos_in_use;
    unsigned int ibos_in_use;

    unsigned int program;


} GraphicalContext;

/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */
GraphicalContext GLCONTEXT;

/* **************************** * PRIVATE FUNCTIONS DEFINITIONS * ***************************** */
void RENDERER_GRAPHICAL_CONTEXT_DEBUG_CALLBACK(SABUGO_ERROR err)
{
    logBegin(err);
    logStr("DEBUG_CALLBACK called in RENDERER/GRAPHICALCONTEXT at");
    switch (err)
    {
	case RENDERER_INIT_GRAPHICAL_CONTEXT_GLEW_INIT_ERROR:
	    logStr("call to glewInit()");
	    break;
	default:
	    break;
    }
    logEnd();
}
void GLdebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf("[OPENGL] Debug Callback error of severity ");
    switch(severity)
    {
	case GL_DEBUG_SEVERITY_HIGH:
	    printf("HIGH");
	    break;
	case GL_DEBUG_SEVERITY_MEDIUM:
	    printf("MEDIUM");
	    break;
	case GL_DEBUG_SEVERITY_LOW:
	    printf("LOW");
	    break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
	    printf("NOTIFICATION");
	    break;
    }
    printf(". Output message:\n%s\n", message);
}
/* ************************** * SEMI PUBLIC FUNCTION DEFINITIONS * *************************** */


void initGraphicalContext(int winBufferWidth, int winBufferHeight)
{
    char* vs;
    char* fs;

    GLCONTEXT.vaos_in_use = 0;
    GLCONTEXT.vbos_in_use = 0;
    GLCONTEXT.ibos_in_use = 0;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
	RENDERER_GRAPHICAL_CONTEXT_DEBUG_CALLBACK(RENDERER_INIT_GRAPHICAL_CONTEXT_GLEW_INIT_ERROR);
	return;
    }
    glViewport(0, 0, winBufferWidth, winBufferHeight);

    /*glEnable(GL_DEBUG_OUTPUT);*/
    glDebugMessageCallback(GLdebugCallback, NULL);

    glGenVertexArrays(1, &GLCONTEXT.vaos[0]);
    glGenBuffers(1, &GLCONTEXT.vbos[0]);
    glGenBuffers(1, &GLCONTEXT.ibos[0]);


    /* Load default shaders */
    vs = shaderSourceStringFromFile(DEFAULT_VERTEX_SHADER);
    fs = shaderSourceStringFromFile(DEFAULT_FRAGMENT_SHADER);
    GLCONTEXT.program = createShadingProgram(vs, fs);
    free(vs);
    free(fs);

    glUseProgram(GLCONTEXT.program);
}

void prepareGraphicalContext()
{
    GLCONTEXT.vaos_in_use = 0;
    GLCONTEXT.vbos_in_use = 0;
    GLCONTEXT.ibos_in_use = 0;
}


void relinquishRenderData(const Vertex* const vertices, unsigned int vcount, DataLayout layout, unsigned int* indexes, unsigned int icount)
{
    unsigned int i;
    GLenum typegl;

    for (i = 0; i < vcount; i++)
    {
	printf("v[%u] = %.3f, %.3f, r=%.3f g=%.3f b=%.3f a=%.3f\n", i, vertices[i].pos[0], vertices[i].pos[1], vertices[i].color[0], vertices[i].color[1], vertices[i].color[2], vertices[i].color[3]);
    }

    for (i = 0; i < icount; i++)
    {
	printf("indexes[%u] = %u\n", i, indexes[i]);
    }
    glBindVertexArray(GLCONTEXT.vaos[GLCONTEXT.vaos_in_use]);

    glBindBuffer(GL_ARRAY_BUFFER, GLCONTEXT.vbos[GLCONTEXT.vbos_in_use]);
    glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLCONTEXT.ibos[GLCONTEXT.ibos_in_use]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), indexes, GL_STATIC_DRAW);

    for (i = 0; i < layout.attributes_count; i++)
    {
	printf("i = %u layout attribute\n", i);
	switch(layout.attributes[i].type)
	{
	    case FLOAT:
		printf("xd");
		typegl = GL_FLOAT;
		break;
	    default:
		printf("DONT COME IN HERE\n");
		return;
	}
	printf("Layout = %u, %u, %s, GL_FALSE, %u %d", i, layout.attributes[i].length, typegl ? "FLOAT" : "ANOTHER", sizeof(Vertex), (void*)layout.attributes[i].offset);

	glVertexAttribPointer(i, layout.attributes[i].length, typegl, GL_FALSE, sizeof(Vertex), (void*)layout.attributes[i].offset);
	glEnableVertexAttribArray(i);
    }



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLCONTEXT.vaos_in_use++;
    GLCONTEXT.vbos_in_use++;
    GLCONTEXT.ibos_in_use++;
}

void drawContextData(unsigned int icount, Primitive mode)
{
    unsigned int i, j;
    GLenum modegl;

    switch(mode)
    {
	case TRIANGLES:
	    modegl = GL_TRIANGLES;
	    break;
	case TRIANGLE_FAN:
	    modegl = GL_TRIANGLE_FAN;
	    break;
	default:
	    return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    printf("vaos in use = %u vbos in use = %u\n", GLCONTEXT.vaos_in_use, GLCONTEXT.vbos_in_use);

    for (i = 0; i < GLCONTEXT.vaos_in_use; i++)
    {
	glBindVertexArray(GLCONTEXT.vaos[i]);

	for (j = 0; j < GLCONTEXT.vbos_in_use; j++)
	{
	    printf("i = %u j = %u\n", i, j);
	    glBindBuffer(GL_ARRAY_BUFFER, GLCONTEXT.vbos[i]);
    	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLCONTEXT.ibos[i]);
	    glDrawElements(modegl, icount, GL_UNSIGNED_INT, 0);

	}
    }
}
/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
/* ************************************* * END OF FILE * ************************************** */
#endif

