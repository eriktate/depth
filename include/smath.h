// S(patial)MATH
#ifndef SMATH_H
#define SMATH_H

#define MATRIX_LENGTH 16

#define IDENTITY_MAT ((mat4){{ 1.0f, 0.0f, 0.0f, 0.0f, \
                              0.0f, 1.0f, 0.0f, 0.0f, \
                              0.0f, 0.0f, 1.0f, 0.0f, \
                              0.0f, 0.0f, 0.0f, 1.0f }})

#define ZERO_MAT ((mat4){{ 1.0f, 0.0f, 0.0f, 0.0f, \
                          0.0f, 1.0f, 0.0f, 0.0f, \
                          0.0f, 0.0f, 1.0f, 0.0f, \
                          0.0f, 0.0f, 0.0f, 1.0f }})


typedef struct mat4 {
	float data[MATRIX_LENGTH];
} mat4;

typedef struct vec2 {
	float x;
	float y;
} vec2;

// creating vectors
vec2 new_vec2(float x, float y);

// creating transform matrices.
mat4 ortho(float l, float r, float b, float t, float n, float f);

mat4 translate(mat4 mat, vec2 translation);
mat4 scale(mat4 mat, vec2 scale);
// uniform scaling for convenience.
mat4 uscale(mat4 mat, float scale);
mat4 rot(mat4 mat, float rad);

vec2 transform(mat4 transform, vec2 target);
mat4 compose(mat4 src, mat4 transform);

// convert transformation to OpenGL compatible buffer.
const float *to_buffer(mat4* transform);

vec2 vec2_add(vec2 left, vec2 right);
vec2 vec2_sub(vec2 left, vec2 right);
float vec2_dot(vec2 left, vec2 right);

vec2 scalar_add2(vec2 vec, float scalar);
vec2 scalar_sub2(vec2 vec, float scalar);
vec2 scalar_mult2(vec2 vec, float scalar);
vec2 scalar_div2(vec2 vec, float scalar);

float mag2(vec2 vec);
vec2 normalize2(vec2 vec);
vec2 negate2(vec2 vec);

float degtorad(float deg);
float radtodeg(float rad);

void print_transform(mat4 transform);

#endif // SMATH_H
