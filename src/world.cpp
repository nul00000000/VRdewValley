#include "world.h"
#include "entity.h"

World::World(int xTiles, int yTiles, double tileSize, double heightMag) {
	GLfloat* verts = new GLfloat[6 * 3];
	for(int i = 0; i < 6; i++) {
		verts[i * 3 + 1] = 0;
	}
	verts[0 * 3 + 0] = -tileSize;
	verts[0 * 3 + 2] = -tileSize;
	verts[1 * 3 + 0] =  tileSize;
	verts[1 * 3 + 2] = -tileSize;
	verts[2 * 3 + 0] =  tileSize;
	verts[2 * 3 + 2] =  tileSize;
	verts[3 * 3 + 0] = -tileSize;
	verts[3 * 3 + 2] = -tileSize;
	verts[4 * 3 + 0] =  tileSize;
	verts[4 * 3 + 2] =  tileSize;
	verts[5 * 3 + 0] = -tileSize;
	verts[5 * 3 + 2] =  tileSize;
	this->terrainMesh = new Model(verts, 6 * 3, 1.0f, 1.0f, 1.0f, true);

	this->entities = std::vector<Entity>();

	entities.push_back(
		Entity((glm::vec3) {0.0f, 0.6f, -1.0f}, new Model(Model::cubeVertices(1, 1, 1),108,0.5,0.5,0.5,false))
	);
}

World::~World() {
	delete terrainMesh;
}

void World::render(BasicShader* shader) {
	shader->loadTransform(glm::identity<glm::mat4>(), 0.3f);

	terrainMesh->render();

	for (auto &entity : entities) {
		entity.render(shader);
		entity.rotate({0.0f, 0.1f, 0.0f});
	}
}
