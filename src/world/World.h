#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include <map>
#include <memory>

#include "Chunk.h"
#include "../libs/PerlinNoise.hpp"


class World
{
public:
    World();

     std::shared_ptr<Chunk> GetChunk(int x, int z) {
        auto key = std::make_pair(x, z);
        return chunks[key];
    }

    auto getChunks() const {
        return chunks;
    }
    Block air = Block(0, false, true);

    Block& getBlock(int x, int y, int z) {
        int X = x;
        int Z = z;
        if(x < 0) X++;
        if(z < 0) Z++;
        auto chunkX = X / config::CHUNK_SIZE;
        auto chunkZ = Z / config::CHUNK_SIZE;
        if (x < 0) chunkX--;
        if (z < 0) chunkZ--;
        auto chunk = GetChunk(chunkX, chunkZ);
        if (chunk == nullptr || y < 0 || y >= config::CHUNK_HEIGHT) {
            return air;
        }
        return const_cast<Block &>(chunk->GetBlock(x % config::CHUNK_SIZE, y, z % config::CHUNK_SIZE));
    }

private:
    void GenerateTerrain();
    void GenerateVegetation();

    float GetHeightValue(int x, int z);
    float GetBiomeValue(int x, int z);

    static void GenerateCactus(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);
    static void GenerateTree(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);

    std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    siv::PerlinNoise perlinHeight;
    siv::PerlinNoise perlinBiome;
};


#endif //MINECRAFT_WORLD_H
