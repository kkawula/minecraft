#ifndef MINECRAFT_CHUNKMESHGENERATOR_H
#define MINECRAFT_CHUNKMESHGENERATOR_H

#include <vector>

#include "../world/World.h"
#include "MeshAtlas.h"

class ChunkMeshGenerator {
public:
    ChunkMeshGenerator(World& world, MeshAtlas& atlas);

    void setupMesh(int chunkX, int chunkZ);
    static void addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face);
    void checkAndAddFace(int chunkX, int chunkZ, int x, int y, int z, Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE], std::vector<float>& vert, int face, int selfType);
    std::vector<float> vert;

private:
    World* world;
    MeshAtlas* atlas;
};


#endif //MINECRAFT_CHUNKMESHGENERATOR_H
