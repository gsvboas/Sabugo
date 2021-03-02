/* ************************************ * START OF FILE * ************************************* */
/* */
/* */
/* */
/* *********************************** * GLOBAL INCLUDES * ************************************ */
#include "Sabugo.h"
#include "Debug/Debug.h"
#include "Core/Log.h"
#include "Renderer/GraphicalContext.h"

#ifdef GLFW_BACKEND
/* **************************** * START OF GLFW IMPLEMENTATION * ****************************** */
#include <GLFW/glfw3.h>
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
typedef struct Window
{
    GLFWwindow* handle;
    int bufferWidth, bufferHeight;
} Window;
typedef struct Core
{
    Window win;
} Core;
/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */
Core CORE;
/* **************************** * PRIVATE FUNCTIONS DEFINITIONS * ***************************** */
void CORE_DEBUG_CALLBACK(SABUGO_ERROR err)
{
    logBegin(err);
    logStr("DEBUG_CALLBACK called in CORE/WINDOW at");
    switch(err)
    {
	case CORE_GLFW_INIT_ERROR:
	    logStr("call to glfwInit()");
	    break;
	case CORE_GLFW_NO_WINDOW_HANDLE_ERROR:
	    logStr("call to glfwCreateWindow()");
	    break;
	default:
	    logStr("UNKNOWN");
	    break;
    }
    logEnd();
}

/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
void createWindow(int width, int height, const char* const name)
{
    if (!glfwInit()){
	CORE_DEBUG_CALLBACK(CORE_GLFW_INIT_ERROR);
	return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    CORE.win.handle = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!CORE.win.handle){
	CORE_DEBUG_CALLBACK(CORE_GLFW_NO_WINDOW_HANDLE_ERROR);
	terminate();
	return;
    }

    glfwMakeContextCurrent(CORE.win.handle);
    glfwGetFramebufferSize(CORE.win.handle, &CORE.win.bufferWidth, &CORE.win.bufferHeight);
    glfwSwapInterval(1); /* VSYNC */

    initGraphicalContext();
}

void terminate()
{
    if (CORE.win.handle)
	glfwDestroyWindow(CORE.win.handle);
    glfwTerminate();
}

void display()
{
    consolidateDrawCalls();
    glfwSwapBuffers(CORE.win.handle);
}

int windowIsOpen()
{
    glfwPollEvents(); /* temporary */
    return !glfwWindowShouldClose(CORE.win.handle);
}
/* ************************************* * END OF FILE * ************************************** */
#endif

