#ifndef MINECRAFT_CHUNKMANAGER_H
#define MINECRAFT_CHUNKMANAGER_H

#include <set>
#include <queue>
#include <thread>

#include "mesh/MeshAtlas.h"
#include "Camera.h"
#include "world/World.h"
#include "mesh/ChunkMeshGenerator.h"

class ChunkManager {
public:
    ChunkManager(MeshAtlas& atlas, Camera &camera, World &world);
    ~ChunkManager();
    void updateCords(int x, int z);
    void updateChunkMesh(int x, int z);
    void addChunksToRender();
    void startChunkGenerationDeamon();
    void exit() {
        running = false;
    }


private:
    MeshAtlas *atlas;
    Camera *camera;
    World *world;

    ChunkMeshGenerator m_chunkMeshGenerator;

    std::queue<std::pair<int, int>> chunksToUpdate;
    std::queue<std::pair<int, int>> chunksToRender;
    std::mutex queueUpdateMutex;
    std::mutex queueRenderMutex;

    std::thread chunkGenerationThread;
    std::thread meshGenerationThread;
    bool running = true;

    void fillQueue(int currX, int currZ);
};


#endif //MINECRAFT_CHUNKMANAGER_H
