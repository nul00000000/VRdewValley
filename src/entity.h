#pragma once

#include "glm/glm.hpp"

#include "model.h"
#include "shader.h"

class Entity {
public:
	Entity(glm::vec3 position, Model *model);
	~Entity();

	glm::vec3 position;
	Model *mModel;

	void render(BasicShader *shader);
};
