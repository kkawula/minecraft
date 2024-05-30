#include "ChunkManager.h"
#include <iostream>
ChunkManager::ChunkManager(MeshAtlas &atlas, Camera &camera, World &world) : m_chunkMeshGenerator(world, atlas) {
    this->atlas = &atlas;
    this->camera = &camera;
    this->world = &world;

    startChunkGenerationThread();

//    updateCords(0, 0);

}

ChunkManager::~ChunkManager() {
    chunkGenerationThread.join();
}

void ChunkManager::fillQueue() {
    std::lock_guard<std::mutex> lock(queueUpdateMutex);
    while (not chunksToUpdate.empty()) {
        chunksToUpdate.pop();
    }
    chunksToUpdate.push(currentCenterChunkPos);

    int currX = currentCenterChunkPos.first - 1;
    int currZ = currentCenterChunkPos.second + 1;
    int currLength = 3;
    std::cout << "staring from" << currX << " " << currZ << std::endl;

    for (int i = 1; i <= config::VIEW_RADIUS; i++) {
        for (int j = 0; j < currLength - 1; j++) {
            chunksToUpdate.emplace(currX, currZ);
            currX++;
        }

        for (int j = 0; j < currLength - 1; j++) {
            chunksToUpdate.emplace(currX, currZ);
            currZ--;
        }

        for (int j = 0; j < currLength - 1; j++) {
            chunksToUpdate.emplace(currX, currZ);
            currX--;
        }

        for (int j = 0; j < currLength - 1; j++) {
            chunksToUpdate.emplace(currX, currZ);
            currZ++;
        }

        currLength += 2;
        currX = currentCenterChunkPos.first - i - 1;
        currZ = currentCenterChunkPos.second + i + 1;
    }
}

void ChunkManager::updateCords(int x, int z) {
    auto cords = atlas->cords();
    currentCenterChunkPos = std::make_pair(x, z);
    fillQueue();

    {
        std::lock_guard<std::mutex> lock(queueRenderMutex);
        std::cout << "Rendering size: " << chunksToRender.size() << std::endl;
        while (not chunksToRender.empty()) {
            auto chunk = chunksToRender.front();
            int i = chunk.first;
            int j = chunk.second;
            chunksToRender.pop();
            atlas->createEntry(i, j);
            m_chunkMeshGenerator.setupMesh(i, j);
            cords->insert(std::make_pair(i, j));
            std::cout << "Rendering chunk: " << i << " " << j << std::endl;
        }
    }

}
void ChunkManager::startChunkGenerationThread() {
    chunkGenerationThread = std::thread([this]() {
        while (true) {
            std::pair<int, int> chunk;
            {
                std::lock_guard<std::mutex> lock(queueUpdateMutex);
                if (chunksToUpdate.empty()) {
                    continue;
                }
                chunk = chunksToUpdate.front();
                chunksToUpdate.pop();
            }

            int i = chunk.first;
            int j = chunk.second;

            if (!world->isChunkGenerated(i, j)) {
                world->generateChunk(i, j);
            }

            {
                std::lock_guard<std::mutex> lock(queueRenderMutex);
                chunksToRender.emplace(i, j);
                std:: cout << "Generating chunk: " << i << " " << j << std::endl;
            }
        }
    });
}

void ChunkManager::updateChunkMesh(int x, int z)
{
    m_chunkMeshGenerator.setupMesh(x, z);
}