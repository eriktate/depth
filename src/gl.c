#include <stdio.h>
#include "gl.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
GLFWwindow *WINDOW = NULL;

int init_window(char *title) {
	if (!glfwInit()) {
		printf("failed to initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	WINDOW = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);
	if (WINDOW == NULL) {
		printf("failed to create GLFW window\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(WINDOW);

	if (gl3wInit()) {
		printf("failed to initialize gl3w\n");
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSwapInterval(0);

	return 0;
}


unsigned int gen_vao() {
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	return vao;
}

unsigned int gen_buffer() {
	unsigned int buf;
	glGenBuffers(1, &buf);

	return buf;
}

void bind_vao(unsigned int id) {
	glBindVertexArray(id);
}

void bind_array_buffer(unsigned int id) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void bind_index_buffer(unsigned int id) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void unbind_vao() {
	glBindVertexArray(0);
}

void unbind_array_buffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void unbind_index_buffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void clear_vao(unsigned int id) {
	glDeleteVertexArrays(1, &id);
}

float fit_x_to_ndc(int width, float x) {
	x = (x / (width / 2)) - 1;

	return x;
}

float fit_y_to_ndc(int height, float y) {
	y = 1 - (y / (height / 2));

	return y;
}

float fit_x_to_screen(int width, float x) {
	x = ((x + 1) / (2 / width));

	return x;
}

// TODO: This is definitely wrong. Need to fix.
float fit_y_to_screen(int height, float y) {
	y = (y / (2 / height));

	return y;
}

vec2 to_screen(vec2 vec) {
	vec.x = fit_x_to_screen(SCREEN_WIDTH, vec.x);
	vec.y = fit_y_to_screen(SCREEN_HEIGHT, vec.y);
	return vec;
}

vec2 from_screen(vec2 vec) {
	vec.x = fit_x_to_ndc(SCREEN_WIDTH, vec.x);
	vec.y = fit_y_to_ndc(SCREEN_HEIGHT, vec.y);

	return vec;
}
