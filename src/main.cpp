#include <stdio.h>

#ifndef GL_INCLUDED
#define GL_INCLUDED
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include "shader.h"
#include "world.h"

#include "vr.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360
#define WINDOW_TITLE "SPEX VR Project"

VRManager* vrm;
World* world;
GLFWwindow* window;
BasicShader* shader;

glm::vec3 camPos(0.0f, 1.0f, 1.0f);

void render(BasicShader* shader) {
	glClearColor(.78, .66, .57, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->render(shader);
}

void glInit() {
	if(!glfwInit()) {
		fprintf(stderr, "Could not initialize GLFW\n");
		exit(1);
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
			WINDOW_TITLE, NULL, NULL);
	if(!window) {
		fprintf(stderr, "Window could not be created\n");
		exit(1);
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
}

void objectsInit() {
	shader = new BasicShader(WINDOW_WIDTH, WINDOW_HEIGHT);
	world = new World(60, 60, 1.0, 10.0);
}

void mainGame() {
	double t;

	shader->use();
	world = new World(600, 600, 1.0, 1.0);

	glm::vec3 camPos(0.0f, 2.0f, 0.0f);

	glm::mat4 camMat;
	glm::mat4 projMat;
	camMat = glm::translate(glm::identity<glm::mat4>(), camPos);
	projMat = glm::perspective(glm::radians(75.0f), 16.0f/9.0f, 0.1f, 180.0f);

	shader->loadCamera(camMat);
	shader->loadProjection(projMat);
	shader->loadSkyLight({1.0f,1.0f,1.0f});
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		vrm->updateInput();
		vrm->render(camPos, shader);

		glfwSwapBuffers(window);
	}

}

int main(int argc, char** argv) {
	printf("Starting\n");
	glInit();
	objectsInit();
	printf("GL initialized\n");
	vrm = new VRManager(&render);
	vrm->setup();
	printf("Starting main loop\n");
	mainGame();
}
