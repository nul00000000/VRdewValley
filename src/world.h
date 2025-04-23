#pragma once

#include "model.h"
#include "shader.h"
#include "entity.h"

class World {
public:
	//for now this just makes a heightmap world
	World(int xTiles, int yTiles, double tileSize, double heightMag);
	~World();
	void render(BasicShader* shader);
	std::vector<Entity> entities;

private:
	Model* terrainMesh;
};
