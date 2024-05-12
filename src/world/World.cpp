#include "World.h"
#include <ctime>
#include <algorithm>
#include <memory>
#include "../config.h"

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

void World::GenerateTerrain(std::vector<std::vector<float>> heightMap, std::vector<std::vector<float>> biomeMap) {
    for (int i = 0; i < config::WORLD_SIZE; ++i) {
        for (int j = 0; j < config::WORLD_SIZE; ++j) {
            std::pair<int, int> chunkPosition = std::make_pair(i, j);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    int globalX = i * config::CHUNK_SIZE + x;
                    int globalZ = j * config::CHUNK_SIZE + z;
                    int height = heightMap[globalX][globalZ] * config::CHUNK_HEIGHT_TO_GENERATE;

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

                        chunk->SetBlock(x, y, z, block);
                    }
                }
            }
            chunks[chunkPosition] = chunk;
        }
    }
}

void World::GenerateVegetation(std::vector<std::vector<float>> heightMap, std::vector<std::vector<float>> biomeMap) {
    for (int i = 0; i < config::WORLD_SIZE; ++i) {
        for (int j = 0; j < config::WORLD_SIZE; ++j) {
            std::shared_ptr<Chunk> chunk = GetChunk(i, j);

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    int globalX = i * config::CHUNK_SIZE + x;
                    int globalZ = j * config::CHUNK_SIZE + z;
                    int y = heightMap[globalX][globalZ] * config::CHUNK_HEIGHT_TO_GENERATE + 1;

                    if(y > config::WATER_LEVEL){
                        if(biomeMap[globalX][globalZ] < 0.3 && chunk->GetBlock(x, y - 1, z).GetType() == Block::SAND) {
                            if (rand() % 100 < 1) {
                                World::GenerateCactus(chunk, x, y, z);
                            }
                        }
                        else if(biomeMap[globalX][globalZ] > 0.8 && heightMap[globalX][globalZ] > 0.8){
                            // mountains
                        }
                        else if(chunk->GetBlock(x, y - 1, z).GetType() == Block::GRASS){
                            if (rand() % 1000 < 15) {
                                if(x >= 2 && x <= 13 && z >= 2 && z <= 13){
                                    World::GenerateTree(chunk, x, y, z);
                                    chunk->SetBlock(x, y - 1, z, Block(Block::DIRT));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /*for(int x = 0; x < config::CHUNK_SIZE * config::WORLD_SIZE; x++){
        for(int z = 0; z < config::CHUNK_SIZE * config::WORLD_SIZE; z++){
            int y = heightMap[x][z] * config::CHUNK_HEIGHT_TO_GENERATE + 1;
            int chunkX = x / config::CHUNK_SIZE;
            int chunkZ = z / config::CHUNK_SIZE;
            std::shared_ptr<Chunk> chunk = GetChunk(chunkX, chunkZ);

            if(y > config::WATER_LEVEL){
                if(biomeMap[x][z] < 0.3 && chunk->GetBlock(x % config::CHUNK_SIZE, y - 1, z % config::CHUNK_SIZE).GetType() == Block::SAND) {
                    if (rand() % 100 < 1) {
                        World::GenerateCactus(chunk, x, y, z);
                    }
                }
                else if(biomeMap[x][z] > 0.8 && heightMap[x][z] > 0.8){
                    // mountains
                }
                else if(chunk->GetBlock(chunkX, y - 1, chunkZ).GetType() == Block::GRASS){
                    if (rand() % 1000 < 10000) {
                        if(chunkX >= 2 && chunkX <= 13 && chunkZ >= 2 && chunkZ <= 13){
                            World::GenerateTree(chunk, chunkX, y, chunkZ);
                            chunk->SetBlock(chunkX, y - 1, chunkZ, Block(Block::DIRT));
                        }
                    }
                }
            }
        }
    }*/
}

void World::GenerateCactus(const std::shared_ptr<Chunk>& chunk, int x, int y, int z) {
    for(int i = 0; i < 3 + rand() % 3; i++){
        auto block = Block(Block::CACTUS);
        chunk->SetBlock(x, y + i, z, block);
    }
}

void World::GenerateTree(const std::shared_ptr<Chunk>& chunk, int x, int y, int z) {
    int trunkHeight = 5 + rand() % 2;
    for(int i = 0; i < trunkHeight; i++){
        auto block = Block(Block::WOOD);
        chunk->SetBlock(x, y + i, z, block);
    }

    int Y = y + trunkHeight - 2;

    std::vector<std::pair<int,int>> leafOffsets1 = {
            // x z
            //first && second level
            {-1,2},{0,2},{1,2},
            {-2,1},{-1,1},{0,1},{1,1},{2,1},
            {-2,0},{-1,0},{1,0},{2,0},
            {-2,-1},{-1,-1},{0,-1},{1,-1},{2,-1},
            {-1,-2},{0,-2},{1,-2}
    };

    std::vector<std::pair<int,int>> leafOffsets2 = {
            // x z
            //third level
            {-1,1},{0,1},{1,1},
            {-1,0},{0,0},{1,0},
            {-1,-1},{0,-1},{1,-1},
    };

    std::vector<std::pair<int,int>> leafOffsets3 = {
            // x z
            //fourth level
            {0,1},
            {-1,0},{0,0},{1,0},
            {0,-1}
    };


    for(int i = 0; i < 2; i++){
        for(const auto& offset : leafOffsets1){
            int xoff = offset.first;
            int zoff = offset.second;
            Block block = Block(Block::LEAF);
            if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
                chunk->SetBlock(x + xoff, Y, z + zoff, block);
            }
        }
        Y++;
    }

    for(const auto& offset : leafOffsets2){
        int xoff = offset.first;
        int zoff = offset.second;
        Block block = Block(Block::LEAF);
        if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
            chunk->SetBlock(x + xoff, Y, z + zoff, block);
        }
    }

    Y++;

    for(const auto& offset : leafOffsets3){
        int xoff = offset.first;
        int zoff = offset.second;
        Block block = Block(Block::LEAF);
        if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
            chunk->SetBlock(x + xoff, Y, z + zoff, block);
        }
    }
}

World::World() : perlinHeight(static_cast<unsigned int>(std::time(nullptr))), perlinBiome(std::rand()) {
    std::vector<std::vector<float>> heightMap = GenerateHeightMap(config::NOISE_WIDTH, config::NOISE_HEIGHT);
    std::vector<std::vector<float>> biomeMap = GenerateBiomeMap(config::NOISE_WIDTH, config::NOISE_HEIGHT, config::BIOME_OCTAVE);

    GenerateTerrain(heightMap, biomeMap);
    GenerateVegetation(heightMap, biomeMap);

}