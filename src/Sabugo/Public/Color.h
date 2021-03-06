#ifndef COLOR_H_
#define COLOR_H_

typedef struct Color
{
    float r, g, b, a;
} Color;

static const Color RED = {1.0f, 0.0f, 0.0f, 1.0f};
static const Color GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
static const Color DARK_GREEN = {0.15f, 0.35f, 0.175f, 1.0f};
static const Color YELLOW = {0.95f, 0.785f, 0.211f, 1.0f};
static const Color BLUE = {0.0f, 0.0f, 1.0f, 1.0f};
static const Color WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
static const Color BLACK = {0.0f, 0.0f, 0.0f, 1.0f};

#endif

