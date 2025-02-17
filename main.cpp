#include <stdio.h>

#include <openxr/openxr.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "i hate unreal engine with a passion"

int main() {
	if(!glfwInit()) {
		fprintf(stderr, "Could not initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
			WINDOW_TITLE, NULL, NULL);
	if(!window) {
		fprintf(stderr, "Window could not be created\n");
		return 1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	int glfwMajor, glfwMinor, glfwRev;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
	uint64_t xrVersion = XrVersion();
	printf("OpenXR version: %d.%d.%d, GLFW version: %d.%d.%d, GL version: %d.%d", 
			XR_VERSION_MAJOR(xrVersion), XR_VERSION_MINOR(xrVersion),
			XR_VERSION_PATCH(xrVersion), glfwMajor, glfwMinor, glfwRev,
			GLVersion.major, GLVersion.minor);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

}