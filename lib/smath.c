#include <stdio.h>
#include <math.h>
#include "smath.h"

#define DEGTORAD 0.0174532925
#define RADTODEG 57.2957795

// key transformation matrix positions
#define TRANSLATE_X 12
#define TRANSLATE_Y 13
#define SCALE_X 0
#define SCALE_Y 5

vec2 new_vec2(float x, float y) {
	return (vec2){
		.x = x,
		.y = y
	};
}

// generate orthographic projection matrix.
// TODO (erik): Is this in column major? Need to find out.
mat4 ortho(float l, float r, float b, float t, float n, float f) {
	return (mat4) {
		.data = {
			1.0f / (r - l), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / (t - b), 0.0f, 0.0f,
			0.0f, 0.0f, (-2.0f) / (f - n), 0.0f,
			-((r + l) / (r - l)), -((t + b) / (t - b)), -((f + n) / (f + n)), 1.0f
		}
	};
}

mat4 translate(mat4 mat, vec2 translation) {
	mat4 transform = IDENTITY_MAT;
	transform.data[TRANSLATE_X] = translation.x;
	transform.data[TRANSLATE_Y] = translation.y;

	return compose(mat, transform);
}

mat4 scale(mat4 mat, vec2 scale) {
	mat4 transform = IDENTITY_MAT;

	transform.data[SCALE_X] = scale.x;
	transform.data[SCALE_Y] = scale.y;

	return compose(mat, transform);
}

mat4 uscale(mat4 mat, float scale) {
	mat4 transform = IDENTITY_MAT;

	// redoing scale computation to remove a matrix copy.
	transform.data[SCALE_X] = scale;
	transform.data[SCALE_Y] = scale;

	return compose(mat, transform);
}

mat4 rot(mat4 mat, float rad) {
	mat4 transform = IDENTITY_MAT;
	float cosine = cosf(rad);
	float sine = sinf(rad);

	transform.data[SCALE_X] = cosine;
	// TODO (erik): Figure out what these transform positions represent.
	transform.data[4] = -sine;
	transform.data[1] = sine;
	transform.data[SCALE_Y] = cosine;

	return compose(mat, transform);
}

vec2 transform(mat4 transform, vec2 target) {
	vec2 result;
	result.x = (transform.data[0] * target.x) +
		(transform.data[4] * target.y) + (transform.data[8] * 1) +
		(transform.data[12] * 1);

	result.y = (transform.data[1] * target.x) +
		(transform.data[5] * target.y) + (transform.data[9] * 1) +
		(transform.data[12] * 1);

	return result;
}

mat4 compose(mat4 left, mat4 right) {
	mat4 result = {
		.data = { 0.0f }
	};

	int idx = 0;
	// iterate down the rows of the left matrix.
	for(int i = 0; i < 4; i++) {
		// iterate across the columns of the right matrix
		for(int j = 0; j < 4; j++) {
			// iterate across the columns of the left matrix and down the rows of the right matrix
			for(int k = 0; k < 4; k++) {
				// right and left flipped to reason about column major formatting.
				result.data[idx] += right.data[(i * 4) + k] * left.data[(k * 4) + j];
			}
			idx++;
		}
	}

	return result;
}

vec2 vec2_add(vec2 left, vec2 right) {
	return new_vec2(left.x + right.x, left.y + right.y);
}

vec2 vec2_sub(vec2 left, vec2 right) {
	return new_vec2(left.x - right.x, left.y - right.y);
}

float vec2_dot(vec2 left, vec2 right) {
	return (left.x * right.x) + (left.y * right.y);
}

vec2 scalar_add2(vec2 vec, float scalar) {
	return new_vec2(vec.x + scalar, vec.y + scalar);
}

vec2 scalar_sub2(vec2 vec, float scalar) {
	return new_vec2(vec.x - scalar, vec.y - scalar);
}

vec2 scalar_mult2(vec2 vec, float scalar) {
	return new_vec2(vec.x * scalar, vec.y * scalar);
}

vec2 scalar_div2(vec2 vec, float scalar) {
	return new_vec2(vec.x / scalar, vec.y / scalar);
}

float mag2(vec2 vec) {
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

vec2 normalize2(vec2 vec) {
	return scalar_div2(vec, mag2(vec));
}

vec2 negate2(vec2 vec) {
	return new_vec2(-vec.x, -vec.y);
}

float degtorad(float deg) {
	return DEGTORAD * deg;
}

float radtodeg(float rad) {
	return RADTODEG * rad;
}

void print_transform(mat4 transform) {
	for(int i = 0; i < 16; i++) {
		printf("%f, ", transform.data[i]);
		if ((i + 1) % 4 == 0) {
			printf("\n");
		}
	}

	printf("\n\n");
}
