#pragma once

#include "model.h"
#include "shader.h"

class World {
    public:
        //for now this just makes a heightmap world
        World(int xTiles, int yTiles, double tileSize, double heightMag);
        ~World();
        void render(BasicShader* shader);
    private:
        Model* terrainMesh;
};