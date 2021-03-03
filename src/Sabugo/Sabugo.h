#ifndef SABUGO_H_
#define SABUGO_H_

/*!
  @file
  */

#include "Public/Math.h"
#include "Public/Color.h"
#include "Public/ShaderType.h"

/* ****************************** * CORE PUBLIC FUNCTIONALITY * ******************************* */
/** \defgroup core Core */ /** @{ */ /* DOXYGEN_CORE_BEGIN */
/** \defgroup window Core/Window */ /** @{ */ /* DOXYGEN_WINDOW_BEGIN */

/** Initializes a window and its graphical context.
    @param width win width.
    @param height win height.
    @param win name */
void createWindow(int width, int height, const char* const name);
/** Cleans up the graphical context created by createWindow(int, int, const char* const) */
void terminate();
/** Displays current frame */
void display();
/** Queries whether window is still open */
int windowIsOpen();

/** @} */ /* DOXYGEN_WINDOW_END */
/** @} */ /* DOXYGEN_CORE_END */




/* **************************** * RENDERER PUBLIC FUNCTIONALITY * ***************************** */
/** \defgroup renderer Renderer */ /** @{ */ /* DOXYGEN_RENDERER_BEGIN */
/** \defgroup shapes Renderer/Shapes */ /** @{ */ /* DOXYGEN_SHAPES_BEGIN */

/** \brief Draws a color-filled triangle to the screen. */
/** Like other shapes' draw functions, drawFillTriangle uses the current shader context (whether it be the default shaders provided by Sabugo or a user-defined shader) to render the geometry.
    @param a, b, c position vectors which define the vertices of the triangle to be drawn.
    @param color rasterization color */
void drawFillTriangle(Vec2f a, Vec2f b, Vec2f c, Color color);

/** \brief Draws a color-filled rectangle to the screen. */
/** Like other shapes' draw functions, drawFillRectangle uses the current shader context (whether it be the default shaders provided by Sabugo or a user-defined shader) to render the geometry.
    @param nw position vector which defines the north-western (up-most, left-most) vertex of the rectangle to be drawn.
    @param dim dimension vector [width, height] of the rectangle to be drawn.
    @param color rasterization color */
void drawFillRectangle(Vec2f nw, Vec2f dim, Color color);

/** \brief Draws a color-filled circle to the screen. */
/** Like other shapes' draw functions, drawFillCircle uses the current shader context (whether it be the default shaders provided by Sabugo or a user-defined shader) to render the geometry. Additionally, due to the way circles are drawn in computer graphics, Sabugo provides facilities for another, more general, drawCircle function. See drawFillCircleCustomDensity (or drawCircleOutlineCustomDensity) for an input on how many vertices should be used in the circle creation.
    @param center position vector which defines the center of the circle to be drawn.
    @param radius radius of the circle to be drawn.
    @param color rasterization color */
void drawFillCircle(Vec2f center, float radius, Color color);

/** \brief Draws a color-filled circle to the screen, with custom density. */
/** This is an extension to the drawFillCircle function, in that it allows the user to decide how many vertices should the circle be defined by. Like other shapes' draw functions, drawFillCircle uses the current shader context (whether it be the default shaders provided by Sabugo or a user-defined shader) to render the geometry.
    @param radius radius of the circle to be drawn.
    @param color rasterization color
    @param density number of vertices that define the circumference */
void drawFillCircleCustomDensity(Vec2f center, float radius, Color color, unsigned int density);
/** @} */ /* DOXYGEN_SHAPES_END */
/** @} */ /* DOXYGEN_RENDERER_END */


/* Scene public functionality */


#endif

