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



void render(BasicShader* shader, World* world) {
	glClearColor(0.3f, 0.9f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->render(shader);
}

GLFWwindow* glInit() {
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
	return window;
}

void mainGame(GLFWwindow* window, VRManager* vr) {
	
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

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		vr->render(camPos, shader, &world);

		glfwSwapBuffers(window);
	}

}

int main(int argc, char** argv) {
	GLFWwindow* window = glInit();
	VRManager vr(&render);
	if((argc > 1 && !strncmp(argv[0], "-d", 2)) || vr.setup()) {
		printf("Desktop Mode\n");
		//desktopington mode
	} else {
		printf("VR Mode\n");

	}
	mainGame(window, &vr);
}
