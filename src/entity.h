#pragma once

#include "glm/glm.hpp"

#include "model.h"
#include "shader.h"

class Entity {
public:
	Entity(glm::vec3 position, Model *model);
	~Entity();

	glm::vec3 position;
	glm::quat rotation;

	Model *mModel;

	void render(BasicShader *shader);

	void translate(glm::vec3 translation);
	void moveTo(glm::vec3 pos);

	void rotate(glm::quat rot);
	void setRotation(glm::quat rot);
};
