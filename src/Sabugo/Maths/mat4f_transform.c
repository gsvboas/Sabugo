#include "Public/Math.h"

void ortho(float left, float right, float bottom, float top, float zNear, float zFar, Mat4f m)
{
    float w_inv = 1.0f / (right - left);
    float h_inv = 1.0f / (bottom - top);
    float d_inv = 1.0f / (zFar - zNear);
    m[0][0] = 2.0f * w_inv; 	m[0][1] = 0.0f; 		m[0][2] = 0.0f; 		m[0][3] = -(right + left) * w_inv;
    m[1][0] = 0.0f; 		m[1][1] = 2.0f * h_inv; 	m[1][2] = 0.0f; 		m[1][3] = -(bottom + top) * h_inv;
    m[2][0] = 0.0f; 		m[2][1] = 0.0f; 		m[2][2] = 2.0f * d_inv; 	m[2][3] = -(zNear * d_inv);
    m[3][0] = 0.0f; 		m[3][1] = 0.0f; 		m[3][2] = 0.0f; 		m[3][3] = 1.0f;
}

