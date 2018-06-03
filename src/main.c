#include <stdbool.h>
#include <stdio.h>
#include "gl.h"


void process_input();


int main(int argc, char *argv[]) {
	// 'floatee' just forces floating windows in my arch install.
	if (init_window("Depth - floatee") != 0) {
		printf("Failed something\n");
		return 1;
	}

	if (WINDOW == NULL) {
		printf("WINDOW is NULL\n");
		return 1;
	}

	while(!glfwWindowShouldClose(WINDOW)) {
		process_input();
	}

	glfwTerminate();
	return 0;
}

void process_input() {
	glfwPollEvents();
	if (glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		printf("Hit esc\n");
		glfwSetWindowShouldClose(WINDOW, true);
	}
}
