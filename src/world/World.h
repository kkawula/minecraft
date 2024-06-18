#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include <map>
#include <memory>
#include <random>
#include <mutex>

#include "Chunk.h"
#include "../libs/PerlinNoise.hpp"

class World {
public:
    World();

     std::shared_ptr<Chunk> GetChunk(int x, int z) {
        auto key = std::make_pair(x, z);
        return chunks[key];
    }

    static std::pair<int, int> GetChunkCords(int x, int z) {
        int X = x;
        int Z = z;
        if(x < 0) X++;
        if(z < 0) Z++;
        auto chunkX = X / config::CHUNK_SIZE;
        auto chunkZ = Z / config::CHUNK_SIZE;
        if (x < 0) chunkX--;
        if (z < 0) chunkZ--;

        return std::make_pair(chunkX, chunkZ);
    }

    //Gets 'in-chunk' cords
    static std::pair<int, int> GetLocalCords(int x, int z) {
        int X = x;
        int Z = z;
        if(x < 0) X++;
        if(z < 0) Z++;

        int xoff = x < 0 ? config::CHUNK_SIZE - 1 : 0;
        int zoff = z < 0 ? config::CHUNK_SIZE - 1 : 0;

        return std::make_pair(X % config::CHUNK_SIZE + xoff, Z % config::CHUNK_SIZE + zoff);
     }

    bool isChunkGenerated(int x, int z) {
         std::lock_guard<std::mutex> lock(worldMutex);
         auto key = std::make_pair(x, z);
         return chunks[key] != nullptr;
     }

    Block& getBlock(int x, int y, int z) {
        auto chunkCords = GetChunkCords(x, z);
        auto chunk = GetChunk(chunkCords.first, chunkCords.second);

        if (chunk == nullptr || y < 0 || y >= config::CHUNK_HEIGHT) {
            std::cout << x << " " << y << " " << z << std::endl;
            throw "Block out of bounds";
        }

        auto chunkLocalCords = GetLocalCords(x, z);
        return chunk->GetBlock_(chunkLocalCords.first, y, chunkLocalCords.second);
    }

    void setBlock(int x, int y, int z, Block block){
        auto chunkCords = GetChunkCords(x, z);
        auto chunk = GetChunk(chunkCords.first, chunkCords.second);

        if (chunk == nullptr || y < 0 || y >= config::CHUNK_HEIGHT) {
            return;
        }

        auto chunkLocalCords = GetLocalCords(x, z);

        chunk->SetBlock(chunkLocalCords.first, y, chunkLocalCords.second, block);
    }

    void generateChunk(int x, int z);

    bool isChunkGenerated(int x, int y, int z) {
        auto chunkCords = GetChunkCords(x, z);
        auto chunk = GetChunk(chunkCords.first, chunkCords.second);
        return chunk != nullptr;
    }

    void addCordsToUpdate(int x, int z)
    {
        cordsToUpdate.emplace_back(x, z);
    }

    void clearCordsToUpdate()
    {
        cordsToUpdate.clear();
    }

    std::vector<std::pair<int, int>> getCordsToUpdate()
    {
        return cordsToUpdate;
    }

private:
    void GenerateTerrain(int i, int j);
    void GenerateVegetation(int i, int j);
    void GenerateOres(int i, int j);
    void GenerateSpecificOre(int i, int j, float frequency, float threshold, int minHeight, int topHeight, int blockType);
    void LayBedrock(int i, int j);

    float GetHeightValue(int x, int z);
    float GetBiomeValue(int x, int z);

    static void GenerateCactus(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);
    static void GenerateTree(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);

    std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    std::mt19937 rng;
    std::uniform_int_distribution<std::int64_t> distribution;

    siv::PerlinNoise perlinHeight;
    siv::PerlinNoise perlinBiome;
    siv::PerlinNoise perlinOre;

    std::vector<std::pair<int, int>> cordsToUpdate = {};

    std::mutex worldMutex;
};


#endif //MINECRAFT_WORLD_H
