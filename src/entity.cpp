#include "entity.h"

Entity::Entity(glm::vec3 position, Model *model) {
	this->position = position;
	this->rotation = glm::quat(1,0,0,0);
	this->mModel = model;
}

Entity::~Entity() {
	//EEeaaaau
	//
	// yeah
}

void Entity::render(BasicShader *shader) {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotation = glm::mat4_cast(this->rotation);
	shader->loadTransform(translation*rotation, 0.1);
	shader->use();
	mModel->render();
}

void Entity::translate(glm::vec3 translation) {
	position += translation;
}

void Entity::moveTo(glm::vec3 pos) {
	position = pos;
}

void Entity::rotate(glm::quat rot) {
	rotation += rotation;
}

void Entity::setRotation(glm::quat rot) {
	rotation = rot;
}
