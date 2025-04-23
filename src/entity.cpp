#include "entity.h"

Entity::Entity(glm::vec3 position, Model *model) {
	this->position = position;
	this->euler_angles = glm::vec3(0.0f);
	this->mModel = model;
}

Entity::~Entity() {
	//EEeaaaau
	//
	// yeah
}

void Entity::render(BasicShader *shader) {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotation = glm::rotate(glm::rotate(glm::rotate(translation,euler_angles[1],(glm::vec3){0,1,0}),euler_angles[2],(glm::vec3){0,0,1}),euler_angles[0],(glm::vec3){1,0,0});
	shader->loadTransform(rotation, 0.1);
	shader->use();
	mModel->render();
}

void Entity::translate(glm::vec3 translation) {
	position += translation;
}

void Entity::rotate(glm::vec3 angle) {
	euler_angles += angle;
}
