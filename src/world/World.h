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

    static std::pair<int, int> GetChunkCords(int globalX, int globalZ) {
        int X = globalX;
        int Z = globalZ;
        if(globalX < 0) X++;
        if(globalZ < 0) Z++;
        auto chunkX = X / config::CHUNK_SIZE;
        auto chunkZ = Z / config::CHUNK_SIZE;
        if (globalX < 0) chunkX--;
        if (globalZ < 0) chunkZ--;

        return std::make_pair(chunkX, chunkZ);
    }

    //Gets 'in-chunk' cords
    static std::pair<int, int> GetLocalCords(int globalX, int globalZ) {
        int X = globalX;
        int Z = globalZ;
        if(globalX < 0) X++;
        if(globalZ < 0) Z++;
        auto chunkX = X / config::CHUNK_SIZE;
        auto chunkZ = Z / config::CHUNK_SIZE;
        if (globalX < 0) chunkX--;
        if (globalZ < 0) chunkZ--;

        int xoff = globalX < 0 ? config::CHUNK_SIZE - 1 : 0;
        int zoff = globalZ < 0 ? config::CHUNK_SIZE - 1 : 0;
        return std::make_pair(X % config::CHUNK_SIZE + xoff, Z % config::CHUNK_SIZE + zoff);
     }

    bool isChunkGenerated(int x, int z) {
        auto key = std::make_pair(x, z);
        return chunks[key] != nullptr;
     }

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
            throw "Block out of bounds";
        }

        int xoff = x < 0 ? config::CHUNK_SIZE - 1 : 0;
        int zoff = z < 0 ? config::CHUNK_SIZE - 1 : 0;
        return chunk->GetBlock_(X % config::CHUNK_SIZE + xoff, y, Z % config::CHUNK_SIZE + zoff);
    }

    void setBlock(int x, int y, int z, Block block){
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
            return;
        }

        int xoff = x < 0 ? config::CHUNK_SIZE - 1 : 0;
        int zoff = z < 0 ? config::CHUNK_SIZE - 1 : 0;
        chunk->SetBlock(X % config::CHUNK_SIZE + xoff, y, Z % config::CHUNK_SIZE + zoff, block);
    }

    void generateChunk(int x, int z);

    bool isChunkGenerated(int x, int y, int z) {
        int X = x;
        int Z = z;
        if(x < 0) X++;
        if(z < 0) Z++;
        auto chunkX = X / config::CHUNK_SIZE;
        auto chunkZ = Z / config::CHUNK_SIZE;
        if (x < 0) chunkX--;
        if (z < 0) chunkZ--;
        auto chunk = GetChunk(chunkX, chunkZ);
        if (chunk == nullptr) {
            return false;
        }
        return true;
    }

    void addCordsToUpdate(int x, int z)
    {
        cordsToUpdate.push_back(std::make_pair(x, z));
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

    float GetHeightValue(int x, int z);
    float GetBiomeValue(int x, int z);

    static void GenerateCactus(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);
    static void GenerateTree(const std::shared_ptr<Chunk>& chunk, int x, int y, int z);

    std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    siv::PerlinNoise perlinHeight;
    siv::PerlinNoise perlinBiome;

    std::vector<std::pair<int, int>> cordsToUpdate = {};
};


#endif //MINECRAFT_WORLD_H
