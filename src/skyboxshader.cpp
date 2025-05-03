#include "shader.h"

#define QUOTE(a) quote_(a)
#define quote_(a) #a

SkyboxShader::SkyboxShader(GLint screenWidth, GLint screenHeight) : Shader((GLchar*)QUOTE(SHADER_BASE) "/shaders/skybox") {
	GLint p;

	// string a((GLchar*)"C:/Users/nulcr/Documents/VRDewValley/shaders/basic");
	//const char* c_str = readFile((char*)(a + ".geom").c_str());
	//geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	//glShaderSource(geometryShaderID, 1, &c_str, NULL);
	//glCompileShader(geometryShaderID);

	// glGetShaderiv(geometryShaderID, GL_COMPILE_STATUS, &p);
	// if (!p) {
	// 	fprintf(stderr, "Geometry shader didn't work go debug it dumbass\n");
	// }
	
	// delete[] c_str;

	// glAttachShader(programID, geometryShaderID);

	bindAttributes();

	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &p);
	if(!p) {
	    fprintf(stderr, "The program won't link, what the fuck did you do\n");
	}
	getUniforms();
	
	glValidateProgram(programID);
	glGetProgramiv(programID, GL_VALIDATE_STATUS, &p);
	if (!p) {
	    fprintf(stderr, "The program won't validate, what the fuck did you do\n");
	}
}

SkyboxShader::~SkyboxShader() {
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);//Don't know if these first 5 lines are inherited or something but
	glDeleteProgram(programID);      //I've put them here anyway just in case
}

void SkyboxShader::bindAttributes() {
	bindAttribute(0, (GLchar*)"position");
	bindAttribute(1, (GLchar*)"color");
	bindAttribute(2, (GLchar*)"normal");
}

void SkyboxShader::getUniforms() {
	transLoc = getUniform((GLchar*)"transform\0");
	camLoc = getUniform((GLchar*)"camera\0");
	projLoc = getUniform((GLchar*)"projection\0");
}

void SkyboxShader::loadProjection(glm::mat4 proj) {
	loadMatrixUniform(4, glm::value_ptr(proj), projLoc);
}

void SkyboxShader::loadTransform(glm::mat4 mTransform) {
	loadMatrixUniform(4, glm::value_ptr(mTransform), transLoc);
}

void SkyboxShader::loadCamera(glm::mat4 mCamera) {
	glm::mat4 temp = glm::inverse(mCamera);
	loadMatrixUniform(4, glm::value_ptr(temp), camLoc);
}
