#ifndef MINECRAFT_CHUNKMANAGER_H
#define MINECRAFT_CHUNKMANAGER_H


#include "mesh/MeshAtlas.h"
#include "Camera.h"
#include "world/World.h"
#include "mesh/ChunkMeshGenerator.h"
#include <set>
#include <queue>

class ChunkManager {
public:
    ChunkManager(MeshAtlas& atlas, Camera &camera, World &world);
    void updateCords(int x, int z);
    void updateChunkMesh(int x, int z);

private:
    MeshAtlas *atlas;
    Camera *camera;
    World *world;

    std::pair<int, int> currentCenterChunkPos = {0, 0};
    std::queue<std::pair<int, int>> chunksToUpdate;

    ChunkMeshGenerator m_chunkMeshGenerator;
};


#endif //MINECRAFT_CHUNKMANAGER_H
