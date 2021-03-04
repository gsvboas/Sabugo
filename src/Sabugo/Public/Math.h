#ifndef MATH_H_
#define MATH_H_

typedef struct Vector2Float
{
    float x, y;
} Vec2f;

typedef struct Vector3UnsignedInt
{
    unsigned int i, j, k;
} Vec3ui;

typedef float Mat4f[4][4];

void ortho(float left, float right, float bottom, float top, float zNear, float zFar, Mat4f m);
#endif

