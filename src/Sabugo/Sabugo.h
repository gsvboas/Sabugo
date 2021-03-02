#ifndef SABUGO_H_
#define SABUGO_H_

/*!
  @file
  */

#include "Public/Math.h"
#include "Public/Color.h"

/* ****************************** * CORE PUBLIC FUNCTIONALITY * ******************************* */
/* Core/Window.c */

/** Initializes a window and its graphical context. @param width win width. @param height win height. @param win name */
void createWindow(int width, int height, const char* const name);
/** Cleans up the graphical context created by createWindow(int, int, const char* const) */
void terminate();
/** Displays current frame*/
void display();
/** Queries whether window is still open */
int windowIsOpen();

/* Rendering public functionality */
/* Renderer/Renderer.c */
/* Renderer/Shapes.c */
void drawTriangle(Vec2f a, Vec2f b, Vec2f c, Color color);
void drawRectangle(Vec2f nw, Vec2f dim, Color color);
/* Scene public functionality */


#endif

