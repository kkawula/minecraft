#include "World.h"
#include <ctime>
#include <algorithm>
#include <memory>
#include "config.h"


std::vector<std::vector<float>> World::GenerateHeightMap(int width, int height) {
    std::vector<std::vector<float>> noiseValues(width, std::vector<float>(height, 0.0f));
    float frequency = 0.01;

    float minNoise = std::numeric_limits<float>::max();
    float maxNoise = std::numeric_limits<float>::min();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int octaves[4] = {3, 6, 12, 24};
            float multipliers[4] = {1.0f, .75f, .5f, .1f};
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
    float frequency = 0.01;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            auto noise = static_cast<float>(perlinBiome.octave2D_01((x * frequency), (y * frequency), octave));
            biomeValues[x][y] = noise;
        }
    }

    return biomeValues;
}

World::World() : perlinHeight(static_cast<unsigned int>(std::time(nullptr))), perlinBiome(std::rand()) {
    std::vector<std::vector<float>> heightMap = GenerateHeightMap(config::NOISE_WIDTH, config::NOISE_HEIGHT);
    std::vector<std::vector<float>> biomeMap = GenerateBiomeMap(config::NOISE_WIDTH, config::NOISE_HEIGHT, config::BIOME_OCTAVE);

    for(int x = 0; x < config::CHUNK_SIZE; x++){
        for(int z = 0; z < config::CHUNK_SIZE; z++){
            biomeMap[x][z] *= heightMap[x][z];
        }
    }

    for (int i = 0; i < config::WORLD_SIZE; ++i) {
        for (int j = 0; j < config::WORLD_SIZE; ++j) {
            std::pair<int, int> chunkPosition = std::make_pair(i, j);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    for (int y = 0; y < config::CHUNK_HEIGHT; ++y) {
                        int globalX = i * config::CHUNK_SIZE + x;
                        int globalZ = j * config::CHUNK_SIZE + z;
                        Block block;

                        if (y <= heightMap[globalX][globalZ] * config::CHUNK_HEIGHT) {
                            if(y <= config::WATER_LEVEL + 3 * biomeMap[globalX][globalZ]){
                                block = Block(7);
                            }
                            else{
                                if(biomeMap[globalX][globalZ] < 0.3){
                                    block = Block(7);
                                } else if(biomeMap[globalX][globalZ] > 0.8 && heightMap[globalX][globalZ] > 0.9){
                                    block = Block(3);
                                } else{
                                    block = Block(0);
                                }
                            }
                        } else if(y <= config::WATER_LEVEL){
                            block = Block(8);
                        } else {
                            block = Block(15, false);
                        }
                        chunk.get()->SetBlock(x, y, z, block);
                    }
                }
            }
            chunk.get()->UpdateMesh();
            chunks[chunkPosition] = chunk;
        }
    }
}