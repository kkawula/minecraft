#include "World.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <memory>

std::vector<std::vector<float>> World::GenerateHeightMap(int width, int height, int octave) {
    std::vector<std::vector<float>> noiseValues(width, std::vector<float>(height, 0.0f));

    int centerX = width / 2;
    int centerY = height / 2;
    float frequency = 0.015;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float distanceToCenterX = std::abs(x - centerX);
            float distanceToCenterY = std::abs(y - centerY);

            float maxDistance = std::max(centerX, centerY);

            float normalizedDistanceX = 1.0f - (distanceToCenterX / maxDistance);
            float normalizedDistanceY = 1.0f - (distanceToCenterY / maxDistance);
            float normalizedDistance = std::min(normalizedDistanceX, normalizedDistanceY);

            float edgeEffect = std::min({distanceToCenterX / centerX, distanceToCenterY / centerY});

            float noise = static_cast<float>(perlin.octave2D_01((x * frequency), (y * frequency), octave));
            float value = noise * normalizedDistance * (1.0f - edgeEffect);

            noiseValues[x][y] = value;
        }
    }

    return noiseValues;
}

std::vector<std::vector<float>> World::GenerateBiomeMap(int width, int height, int octave) {
    std::vector<std::vector<float>> biomeValues(width, std::vector<float>(height, 0.0f));
    float frequency = 0.005;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float noise = static_cast<float>(perlin.octave2D_01((x * frequency), (y * frequency), octave));
            biomeValues[x][y] = noise;
        }
    }

    return biomeValues;
}

//World::World() : perlin(123456u) {
World::World() : perlin(static_cast<unsigned int>(std::time(nullptr))) {
    std::vector<std::vector<float>> heightMap = GenerateHeightMap(NOISE_WIDTH, NOISE_HEIGHT, NOISE_OCTAVE);
    std::vector<std::vector<float>> biomeMap = GenerateBiomeMap(NOISE_WIDTH, NOISE_HEIGHT, BIOME_OCTAVE);

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            biomeMap[x][z] *= heightMap[x][z];
        }
    }

    for (int i = 0; i < WORLD_SIZE; ++i) {
        for (int j = 0; j < WORLD_SIZE; ++j) {
            std::pair<int, int> chunkPosition = std::make_pair(i, j);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                        int globalX = i * CHUNK_SIZE + x;
                        int globalZ = j * CHUNK_SIZE + z;
                        Block block;

                        if (y <= heightMap[globalX][globalZ] * CHUNK_HEIGHT) {
                            if(y <= WATER_LEVEL + 3){
                                block = Block(7);
                            }
                            else{
                                if(biomeMap[globalX][globalZ] < 0.3){
                                    block = Block(7);
                                } else if(biomeMap[globalX][globalZ] < 0.55){
                                    block = Block(0);
                                } else{
                                    block = Block(3);
                                }
                            }
                        } else if(y <= WATER_LEVEL){
                            block = Block(8);
                        } else {
                            block = Block(0, false);
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