#define GLEW_STATIC
#include "sabugo/Sabugo.h"
#include "vendor/GL/glew.h"
#include "vendor/GLFW/glfw3.h"

#include "sabugo/renderer/renderer.h"

typedef struct SabugoWindow
{
    GLFWwindow* handle;
    int bw, bh;
} SabugoWindow;

typedef struct SabugoCore
{
    SabugoWindow win;
} SabugoCore;

SabugoCore CORE;

void createWindow(int width, int height, const char* const name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    CORE.win.handle = glfwCreateWindow(800, 600, "Sabugo Window", NULL, NULL);
    glfwMakeContextCurrent(CORE.win.handle);
    glfwSwapInterval(1);
    glfwGetFramebufferSize(CORE.win.handle, &CORE.win.bw, &CORE.win.bh);

    initRenderer(CORE.win.bw, CORE.win.bh);

}

int windowIsOpen()
{
    glfwPollEvents();
    return !glfwWindowShouldClose(CORE.win.handle);
}

void display()
{
    glfwSwapBuffers(CORE.win.handle);
}

void terminate()
{
    if (CORE.win.handle)
	glfwDestroyWindow(CORE.win.handle);
    glfwTerminate();
}

