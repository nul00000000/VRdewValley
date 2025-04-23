#pragma once

#include "model.h"
#include "shader.h"
#include "power.h"
#include "entity.h"

class World {
public:
	//for now this just makes a heightmap world
	World(int xTiles, int yTiles, double tileSize, double heightMag);
	~World();
	void render(BasicShader* shader);
	double getWeather(double t);

	void update(double t);

	std::vector<Entity> entities;
	Power *power;

private:
	Model* terrainMesh;
};
