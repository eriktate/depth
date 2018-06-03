#ifndef GL_H
#define GL_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "smath.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern GLFWwindow *WINDOW;

int init_window(char *title);

// helpers with nicer names than native OpenGL calls
unsigned int gen_vao();
unsigned int gen_buffer();

void bind_vao(unsigned int id);
void bind_array_buffer(unsigned int id);
void bind_index_buffer(unsigned int id);

void unbind_vao();
void unbind_array_buffer();
void unbind_index_buffer();
void clear_vao(unsigned int id);

vec2 to_screen(vec2 vec);
vec2 from_screen(vec2 vec);

#endif //GL_H
