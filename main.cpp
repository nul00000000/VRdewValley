#include <stdio.h>

#include <openxr/openxr.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "i hate unreal engine with a passion"

int main() {
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
			WINDOW_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	int glfwMajor, glfwMinor, glfwRev;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
	uint64_t xrVersion = XrVersion();
	printf("OpenXR version: %d.%d.%d, GLFW verision: %d.%d.%d", 
			XR_VERSION_MAJOR(xrVersion), XR_VERSION_MINOR(xrVersion),
			XR_VERSION_PATCH(xrVersion), glfwMajor, glfwMinor, glfwRev);

}