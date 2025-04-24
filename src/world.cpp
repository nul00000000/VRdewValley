#include "world.h"
#include "entity.h"

#include <glm/gtc/noise.hpp>

World::World(int xTiles, int yTiles, double tileSize, double heightMag) {

	GLfloat* verts = new GLfloat[6 * 3 * xTiles * yTiles];
	float scale = 10.0;

	for(int x = 0; x < xTiles; x++) {
		for(int y = 0; y < yTiles; y++) {
			verts[(x+y*xTiles)*18 +  0] = (x+1-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  2] = (y+1-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  1] = heightMag *
				glm::perlin((glm::vec2) {((float) x+1)/scale, ((float) y+1)/scale});

			verts[(x+y*xTiles)*18 +  3] = (x+0-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  5] = (y+0-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  4] = heightMag *
				glm::perlin((glm::vec2) {((float) x+0)/scale, ((float) y+0)/scale});

			verts[(x+y*xTiles)*18 +  6] = (x+1-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  8] = (y+0-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 +  7] = heightMag *
				glm::perlin((glm::vec2) {((float) x+1)/scale, ((float) y+0)/scale});

			verts[(x+y*xTiles)*18 +  9] = (x+0-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 11] = (y+1-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 10] = heightMag *
				glm::perlin((glm::vec2) {((float) x+0)/scale, ((float) y+1)/scale});

			verts[(x+y*xTiles)*18 + 12] = (x+0-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 14] = (y+0-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 13] = heightMag *
				glm::perlin((glm::vec2) {((float) x+0)/scale, ((float) y+0)/scale});

			verts[(x+y*xTiles)*18 + 15] = (x+1-xTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 17] = (y+1-yTiles/2)*tileSize;
			verts[(x+y*xTiles)*18 + 16] = heightMag *
				glm::perlin((glm::vec2) {((float) x+1)/scale, ((float) y+1)/scale});
		}
	}

	this->terrainMesh = new Model(verts, 6 * 3 * xTiles * yTiles, 1.0f, 1.0f, 1.0f, true);

	this->entities = std::vector<Entity>();

	entities.push_back(
		Entity((glm::vec3) {0.0f, 0.6f, -1.0f}, new Model(Model::cubeVertices(1, 1, 1),108,0.5,0.5,0.5,false))
	);
	entities.push_back(
		Entity((glm::vec3) {1.0f, 0.6f, -1.0f}, new Model(Model::cubeVertices(.1, .1, .2),108,0.5,0.5,0.5,false))
	);

	power = new Power(1.0, 2.0);
}

World::~World() {
	delete terrainMesh;
}

void World::render(BasicShader* shader) {
	shader->loadTransform(glm::identity<glm::mat4>(), 0.3f);

	terrainMesh->render();

	//for (auto &entity : entities) {
		// entity.render(shader);
		// entity.rotate({0.0f, 0.001f * ((float) rand())/RAND_MAX, 0.0f});
	//}
}

double World::getWeather(double t) {
	return glm::perlin((glm::vec2) {t*0.001,0});
}
