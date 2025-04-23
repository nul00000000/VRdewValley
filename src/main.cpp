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
	//report openvr version here

	BasicShader* shader = new BasicShader(WINDOW_WIDTH, WINDOW_HEIGHT);
	shader->use();
	World world(60, 60, 1.0, 10.0);

	glm::vec3 camPos(0.0f, 1.0f, 1.0f);
	glm::mat4 camMat;
	glm::mat4 projMat;
	camMat = glm::translate(glm::identity<glm::mat4>(), -camPos);
	projMat = glm::perspective(glm::radians(75.0f), 16.0f/9.0f, 0.1f, 180.0f);

	shader->loadCamera(camMat);
	shader->loadProjection(projMat);
	shader->loadSkyLight({1.0f,1.0f,1.0f});

	double t;

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		double weather = world.getWeather(t);

		t++;

		glClearColor(0.9f*weather, 0.1f*weather, 0.2f*weather, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.render(shader);
		// terrainMesh->render();

		glfwSwapBuffers(window);
	}

}

int main() {
	printf("penis among us\n");
	mainGame();
	VRManager vr;
	vr.setup();
}
