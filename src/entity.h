#pragma once

#include "glm/glm.hpp"

#include "model.h"
#include "shader.h"

class Entity {
public:
	Entity(glm::vec3 position, Model *model);
	~Entity();

	glm::vec3 position;
	glm::vec3 euler_angles;

	Model *mModel;

	void render(BasicShader *shader);

	void translate(glm::vec3 translation);

	void rotate(glm::vec3 uh);
};
