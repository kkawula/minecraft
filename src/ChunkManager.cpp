#include "ChunkManager.h"
#include <iostream>
#include <chrono>
ChunkManager::ChunkManager(MeshAtlas &atlas, Camera &camera, World &world) : m_chunkMeshGenerator(world, atlas) {
    this->atlas = &atlas;
    this->camera = &camera;
    this->world = &world;

    startChunkGenerationDeamon();
}

ChunkManager::~ChunkManager() {
    chunkGenerationThread.join();
}

void ChunkManager::fillQueue(int currX, int currZ) {
    std::lock_guard<std::mutex> lock(queueUpdateMutex);
    while (not chunksToUpdate.empty()) {
        chunksToUpdate.pop();
    }
    chunksToUpdate.emplace(currX, currZ);

    int currLength = 3;

    for (int i = 1; i <= config::VIEW_RADIUS; i++) {
        for (int j = 0; j < currLength - 1; j++) {
            if (not world->isChunkGenerated(currX, currZ))
                chunksToUpdate.emplace(currX, currZ);
            currX++;
        }

        for (int j = 0; j < currLength - 1; j++) {
            if (not world->isChunkGenerated(currX, currZ))
                chunksToUpdate.emplace(currX, currZ);
            currZ--;
        }

        for (int j = 0; j < currLength - 1; j++) {
            if (not world->isChunkGenerated(currX, currZ))
                chunksToUpdate.emplace(currX, currZ);
            currX--;
        }

        for (int j = 0; j < currLength - 1; j++) {
            if (not world->isChunkGenerated(currX, currZ))
                chunksToUpdate.emplace(currX, currZ);
            currZ++;
        }

        currLength += 2;
        currX = currentCenterChunkPos.first - i - 1;
        currZ = currentCenterChunkPos.second + i + 1;
    }
}

void ChunkManager::updateCords(int x, int z) {
    fillQueue(x, z);
}

void ChunkManager::addChunksToRendering() {
    auto cords = atlas->cords();

    {
        std::lock_guard<std::mutex> lock(queueRenderMutex);
        while (not chunksToRender.empty()) {
            auto chunk = chunksToRender.front();
            chunksToRender.pop();
            int i = chunk.first;
            int j = chunk.second;

            bool flag = false;
            for (int k = -1; k <= 1; k++) {
                for (int n = -1; n <= 1; n++) {
                    if (k == 0 && n == 0) {
                        continue;
                    }
                    auto cords = atlas->cords();
                    if (not world->isChunkGenerated(chunk.first + k, chunk.second + n)) {
                        flag = true;
                        break;
                    }

                }
                if (flag) {
                    break;
                }
            }
            if (flag) {
                chunksToRender.emplace(i, j);
                break;
            }

            atlas->createEntry(i, j);
            m_chunkMeshGenerator.setupMesh(i, j);
            cords->insert(std::make_pair(i, j));

        }
    }

}
void ChunkManager::startChunkGenerationDeamon() {
    chunkGenerationThread = std::thread([this]() {
        while (running) {
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
            }
            std::this_thread::sleep_for(std::chrono::milliseconds (5));

        }
    });
}

void ChunkManager::updateChunkMesh(int x, int z)
{
    m_chunkMeshGenerator.setupMesh(x, z);
}