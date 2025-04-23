#include <stdio.h>

#include <openxr/openxr.h>
#ifndef GL_INCLUDED
#define GL_INCLUDED
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include "shader.h"
#include "world.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "SPEX VR Project"

void mainGame() {
	if(!glfwInit()) {
		fprintf(stderr, "Could not initialize GLFW\n");
		exit(1);
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
			WINDOW_TITLE, NULL, NULL);
	if(!window) {
		fprintf(stderr, "Window could not be created\n");
		exit(1);
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	int glfwMajor, glfwMinor, glfwRev;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
	uint64_t xrVersion = XrVersion();
	printf("OpenXR version: %d.%d.%d, GLFW version: %d.%d.%d, GL version: %d.%d\n", 
			XR_VERSION_MAJOR(xrVersion), XR_VERSION_MINOR(xrVersion),
			XR_VERSION_PATCH(xrVersion), glfwMajor, glfwMinor, glfwRev,
			GLVersion.major, GLVersion.minor);

	BasicShader* shader = new BasicShader(1280, 720);
	shader->use();
	World world(1, 1, 1.0, 1.0);

	glm::vec3 camPos(1.0, 1.0f, 0.0);
	glm::mat4 camMat;
	glm::mat4 projMat;
	camMat = glm::translate(glm::identity<glm::mat4>(), camPos);
	projMat = glm::perspective(35.0f, 9.0f/16.0f, 0.1f, 100.0f);

	shader->loadCamera(camMat);
	shader->loadProjection(projMat);
	shader->loadSkyLight({1.0f,1.0f,1.0f});

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.3f, 0.9f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		world.render(shader);
		// terrainMesh->render();

		glfwSwapBuffers(window);
	}

}

int main() {
	mainGame();
}