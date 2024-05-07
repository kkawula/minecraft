#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include <map>

#include "Chunk.h"
#include "libs/PerlinNoise.hpp"


class World
{
public:
    World();

    const Chunk& GetChunk(int x, int z) const {
        auto key = std::make_pair(x, z);
        return chunks.at(key);
    }

    auto getChunks() const {
        return chunks;
    }

private:
    static constexpr int CHUNK_SIZE = Chunk::CHUNK_SIZE;
    //static constexpr int CHUNK_HEIGHT = Chunk::CHUNK_HEIGHT / 2;
    static constexpr int CHUNK_HEIGHT = 100;
    static constexpr int WORLD_SIZE = 20;
    static constexpr int BIOME_OCTAVE = 3;
    static constexpr int NOISE_WIDTH = CHUNK_SIZE * WORLD_SIZE;
    static constexpr int NOISE_HEIGHT = CHUNK_SIZE * WORLD_SIZE;
    static constexpr int WATER_LEVEL = CHUNK_HEIGHT / 2;

    std::vector<std::vector<float>> GenerateHeightMap(int width, int height);
    std::vector<std::vector<float>> GenerateBiomeMap(int width, int height, int octave);

    std::map<std::pair<int, int>, Chunk> chunks;

    siv::PerlinNoise perlinHeight;
    siv::PerlinNoise perlinBiome;
};


#endif //MINECRAFT_WORLD_H
