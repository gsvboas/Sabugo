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

#include <stdio.h>
#include <stdlib.h>

#ifdef GL_BACKEND
/* ***************************** * START OF GL IMPLEMENTATION * ******************************* */
#include <GL/glew.h>
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
#define VERTICES_MAX_BUFFER 10
#define INDEXES_MAX_BUFFER 10
typedef struct Vertex
{
    float pos[2];
} Vertex;
typedef struct GraphicalContext
{
    /* OpenGL id's */
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
    unsigned int program;

    /* CPU data buffers */
    Vertex vertices[VERTICES_MAX_BUFFER];
    unsigned int vertices_count;

    unsigned int indexes[INDEXES_MAX_BUFFER];
    unsigned int indexes_count;


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
unsigned int appendVertexToVertices(Vec2f v, Color color)
{
    GLCONTEXT.vertices[GLCONTEXT.vertices_count].pos[0] = v.x;
    GLCONTEXT.vertices[GLCONTEXT.vertices_count].pos[1] = v.y;
    GLCONTEXT.vertices_count++;
    return GLCONTEXT.vertices_count - 1;
}

void appendIndexToIndexes(unsigned int index)
{
    GLCONTEXT.indexes[GLCONTEXT.indexes_count] = index;
    GLCONTEXT.indexes_count++;
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
void initGraphicalContext(int winBufferWidth, int winBufferHeight)
{
    char* vs;
    char* fs;

    GLCONTEXT.indexes_count = 0;
    GLCONTEXT.vertices_count = 0;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
	RENDERER_GRAPHICAL_CONTEXT_DEBUG_CALLBACK(RENDERER_INIT_GRAPHICAL_CONTEXT_GLEW_INIT_ERROR);
	return;
    }
    glViewport(0, 0, winBufferWidth, winBufferHeight);

    /*glEnable(GL_DEBUG_OUTPUT);*/
    glDebugMessageCallback(GLdebugCallback, NULL);

    glGenVertexArrays(1, &GLCONTEXT.vao);
    glBindVertexArray(GLCONTEXT.vao);

    glGenBuffers(1, &GLCONTEXT.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, GLCONTEXT.vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &GLCONTEXT.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLCONTEXT.vbo);

    /* Load default shaders */
    vs = shaderSourceStringFromFile(DEFAULT_VERTEX_SHADER);
    fs = shaderSourceStringFromFile(DEFAULT_FRAGMENT_SHADER);
    GLCONTEXT.program = createShadingProgram(vs, fs);
    free(vs);
    free(fs);

    glUseProgram(GLCONTEXT.program);
}


void consolidateDrawCalls()
{
    unsigned int i;

    printf("VERTICES\n");
    for (i = 0; i < GLCONTEXT.vertices_count; i++)
    {
	printf("x = %.3f y = %.3f\n", GLCONTEXT.vertices[i].pos[0], GLCONTEXT.vertices[i].pos[1]);
    }
    printf("INDEXES\n");
    for (i = 0; i < GLCONTEXT.indexes_count; i++)
    {
	printf("x = %u y = %u\n", GLCONTEXT.indexes[i], GLCONTEXT.indexes[i]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, GLCONTEXT.vbo);
    glBufferData(GL_ARRAY_BUFFER, GLCONTEXT.vertices_count * 2 * sizeof(float), GLCONTEXT.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLCONTEXT.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLCONTEXT.indexes_count * sizeof(unsigned int), GLCONTEXT.indexes, GL_STATIC_DRAW);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, GLCONTEXT.indexes_count, GL_UNSIGNED_INT, 0);
    /*glDrawArrays(GL_TRIANGLES, 0, GLCONTEXT.vertices_count);*/
    printf("%u\n", GLCONTEXT.vertices_count);

    GLCONTEXT.vertices_count = 0;
    GLCONTEXT.indexes_count = 0;

}
/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
/* ************************************* * END OF FILE * ************************************** */
#endif

