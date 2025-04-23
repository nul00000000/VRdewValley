#include "entity.h"

Entity::Entity(glm::vec3 position, Model *model) {
	this->position = position;
	this->mModel = model;
}

Entity::~Entity() {
	//EEeaaaau
}

void Entity::render(BasicShader *shader) {
	shader->loadTransform(glm::translate(glm::mat4(1.0f), position), 0.1);
	shader->use();
	mModel->render();
}
