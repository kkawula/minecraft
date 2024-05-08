#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include <map>
#include <memory>

#include "Chunk.h"
#include "libs/PerlinNoise.hpp"


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

private:

    std::vector<std::vector<float>> GenerateHeightMap(int width, int height);
    std::vector<std::vector<float>> GenerateBiomeMap(int width, int height, int octave);
    static void GenerateCactus(std::shared_ptr<Chunk> chunk, int x, int y, int z);

    std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    siv::PerlinNoise perlinHeight;
    siv::PerlinNoise perlinBiome;
};


#endif //MINECRAFT_WORLD_H
