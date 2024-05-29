#include "ChunkManager.h"
#include <iostream>
ChunkManager::ChunkManager(MeshAtlas &atlas, Camera &camera, World &world) : m_chunkMeshGenerator(world, atlas) {
    this->atlas = &atlas;
    this->camera = &camera;
    this->world = &world;

    // ***********
    // #TODO get chunk cords based on camera position
    int x = 0;
    int z = 0;
    // *****

    auto cords = atlas.cords();
    cords->clear();
    for (int i = -config::VIEW_RADIUS; i <= config::VIEW_RADIUS; i++) {
        for (int j = -config::VIEW_RADIUS; j <= config::VIEW_RADIUS; j++) {
            if (not world.isChunkGenerated(i, j)) {
                world.generateChunk(i, j);
            }

        }
    }

    for (int i = -config::VIEW_RADIUS; i <= config::VIEW_RADIUS; i++) {
        for (int j = -config::VIEW_RADIUS; j <= config::VIEW_RADIUS; j++) {
            if (not atlas.isMeshGenerated(i, j)) {
                atlas.createEntry(i, j);
                m_chunkMeshGenerator.setupMesh(i, j);
            }
            cords->insert(std::make_pair(i, j));
        }
    }

}

void ChunkManager::updateCords(int x, int z) {
    auto cords = atlas->cords();
//    cords->clear();
    for (int i = -config::VIEW_RADIUS + x; i <= config::VIEW_RADIUS + x; i++) {
        for (int j = -config::VIEW_RADIUS + z; j <= config::VIEW_RADIUS + z; j++) {
            if (i < 1 || j < 1) continue; // TODO delete

            if (not world->isChunkGenerated(i, j)) {
                world->generateChunk(i, j);
            }

            if (world->isChunkGenerated(i, j)) {
                if (not atlas->isMeshGenerated(i, j)) {
                    atlas->createEntry(i, j);
                    // to avoid rendering sides of chunk TODO to rework
                    std::pair<int, int> arr[]= {{1,0}, {0,1}, {-1,0}, {0,-1}};
                    for (auto vec : arr) {
                        if (not world->isChunkGenerated(i + vec.first, j + vec.second))
                            world->generateChunk(i + vec.first, j + vec.second);
                    }
                    // end
                    m_chunkMeshGenerator.setupMesh(i, j);
                }
                cords->insert(std::make_pair(i, j));
            }

        }
    }
}

void ChunkManager::updateChunkMesh(int x, int z)
{
    m_chunkMeshGenerator.setupMesh(x, z);
}