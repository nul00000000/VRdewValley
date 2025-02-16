#include <iostream>

#include <openxr/openxr.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	printf("OpenXR version: %d.%d, Glad verision:", XR_VERSION_MAJOR(XrVersion()), XR_VERSION_MINOR(XrVersion()));  
}