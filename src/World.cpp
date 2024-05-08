#include "World.h"
#include <ctime>
#include <algorithm>
#include <memory>
#include "config.h"


std::vector<std::vector<float>> World::GenerateHeightMap(int width, int height) {
    std::vector<std::vector<float>> noiseValues(width, std::vector<float>(height, 0.0f));
    float frequency = 0.008;

    float minNoise = std::numeric_limits<float>::max();
    float maxNoise = std::numeric_limits<float>::min();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int octaves[4] = {3, 6, 12, 24};
            float multipliers[4] = {1.0f, .5f, .25f, .125f};
            noiseValues[x][y] = 0;

            for(int i = 0; i < 4; i++){
                auto noise = static_cast<float>(perlinHeight.octave2D_01((x * frequency), (y * frequency), octaves[i]));
                noiseValues[x][y] += noise * multipliers[i];

                minNoise = std::min(minNoise, noiseValues[x][y]);
                maxNoise = std::max(maxNoise, noiseValues[x][y]);
            }
        }
    }

    float range = maxNoise - minNoise;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            noiseValues[x][y] = (noiseValues[x][y] - minNoise) / range;
        }
    }

    return noiseValues;
}

std::vector<std::vector<float>> World::GenerateBiomeMap(int width, int height, int octave) {
    std::vector<std::vector<float>> biomeValues(width, std::vector<float>(height, 0.0f));
    float frequency = 0.005;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            auto noise = static_cast<float>(perlinBiome.octave2D_01((x * frequency), (y * frequency), octave));
            biomeValues[x][y] = noise;
        }
    }

    return biomeValues;
}

void World::GenerateCactus(std::shared_ptr<Chunk> chunk, int x, int y, int z){
    for(int i = 0; i < 3 + rand() % 3; i++){
        auto block = Block(Block::CACTUS);
        chunk->SetBlock(x, y + i, z, block);
    }
}

World::World() : perlinHeight(static_cast<unsigned int>(std::time(nullptr))), perlinBiome(std::rand()) {
    std::vector<std::vector<float>> heightMap = GenerateHeightMap(config::NOISE_WIDTH, config::NOISE_HEIGHT);
    std::vector<std::vector<float>> biomeMap = GenerateBiomeMap(config::NOISE_WIDTH, config::NOISE_HEIGHT, config::BIOME_OCTAVE);

    for (int i = 0; i < config::WORLD_SIZE; ++i) {
        for (int j = 0; j < config::WORLD_SIZE; ++j) {
            std::pair<int, int> chunkPosition = std::make_pair(i, j);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    int globalX = i * config::CHUNK_SIZE + x;
                    int globalZ = j * config::CHUNK_SIZE + z;
                    int height = heightMap[globalX][globalZ] * config::CHUNK_HEIGHT;

                    for (int y = 0; y < config::CHUNK_HEIGHT; ++y) {
                        Block block;

                        if (y <= height) {
                            int dirtAppearingHeight = 1;
                            int rockAppearingHeight = 3;
                            if (y <= config::WATER_LEVEL + 3 * biomeMap[globalX][globalZ]) {
                                block = Block(Block::SAND);
                                dirtAppearingHeight = 3;
                                rockAppearingHeight = 5;
                            } else {
                                if (biomeMap[globalX][globalZ] < 0.3) {
                                    block = Block(Block::SAND);
                                    dirtAppearingHeight = 3;
                                    rockAppearingHeight = 5;
                                } else if (biomeMap[globalX][globalZ] > 0.8 && heightMap[globalX][globalZ] > 0.8) {
                                    block = Block(Block::ROCK);
                                    dirtAppearingHeight = config::CHUNK_HEIGHT; // so that it doesn't appear
                                    rockAppearingHeight = 1;
                                } else {
                                    block = Block(Block::GRASS);
                                }
                            }

                            if(y <= height - rockAppearingHeight){
                                block = Block(Block::ROCK);
                            }
                            else if(y <= height - dirtAppearingHeight){
                                block = Block(Block::DIRT);
                            }
                        } else if(y <= config::WATER_LEVEL){
                            block = Block(Block::WATER, false, true);
                        } else if(chunk->GetBlock(x, y, z).GetType() == Block::AIR){
                            block = Block(Block::AIR, false, true);
                        }

                        if(y == height + 1 && biomeMap[globalX][globalZ] < 0.3 && y > config::WATER_LEVEL){
                            if(rand() % 100 < 1){
                                World::GenerateCactus(chunk, x, y, z);
                            }
                        }

                        if(chunk->GetBlock(x, y, z).GetType() == Block::AIR)
                            chunk->SetBlock(x, y, z, block);
                    }
                }
            }
            chunk->UpdateMesh();
            chunks[chunkPosition] = chunk;
        }
    }
}