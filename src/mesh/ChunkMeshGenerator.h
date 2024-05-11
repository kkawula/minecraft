#ifndef MINECRAFT_CHUNKMESHGENERATOR_H
#define MINECRAFT_CHUNKMESHGENERATOR_H

#include "../world/World.h"
#include <vector>

class ChunkMeshGenerator {
public:
    ChunkMeshGenerator(World& world);

    void setupMeshes();
    void addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face);

    std::vector<float> vert;
private:
    World* world;

};


#endif //MINECRAFT_CHUNKMESHGENERATOR_H
