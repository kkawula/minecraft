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
    static constexpr int CHUNK_HEIGHT = Chunk::CHUNK_HEIGHT;
    static constexpr int WORLD_SIZE = 20;
    static constexpr int NOISE_OCTAVE = 12;
    static constexpr int NOISE_WIDTH = CHUNK_SIZE * WORLD_SIZE;
    static constexpr int NOISE_HEIGHT = CHUNK_SIZE * WORLD_SIZE;

    std::vector<std::vector<float>> GeneratePerlinNoise(int width, int height, int octave);

    std::map<std::pair<int, int>, Chunk> chunks;

    siv::PerlinNoise perlin;
};


#endif //MINECRAFT_WORLD_H
