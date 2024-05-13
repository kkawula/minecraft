#include "World.h"
#include <ctime>
#include <algorithm>
#include <memory>

float World::GetHeightValue(int x, int z) {
    float frequency = 0.004;
    int octaves[4] = {3, 6, 9, 12};
    float multipliers[4] = {.8f, .5f, .25f, .125f};
    float res = 0.0f;

    for(int i = 0; i < 4; i++){
        auto noise = static_cast<float>(perlinHeight.octave2D_01((x * frequency), (z * frequency), octaves[i]));
        res += noise * multipliers[i];
    }

    res *= 0.5;
    res = pow(res, 3);

    return res;
}

float World::GetBiomeValue(int x, int z) {
    float frequency = 0.001;

    return static_cast<float>(perlinBiome.octave2D_01((x * frequency), (z * frequency), config::BIOME_OCTAVE));
}

void World::GenerateTerrain() {
    for (int i = config::WORLD_MIN_X; i <= config::WORLD_MAX_X; ++i) {
        for (int j = config::WORLD_MIN_Z; j <= config::WORLD_MAX_Z; ++j) {
            std::pair<int, int> chunkPosition = std::make_pair(i, j);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    int globalX = i * config::CHUNK_SIZE + x;
                    int globalZ = j * config::CHUNK_SIZE + z;

                    float heightValue = GetHeightValue(globalX, globalZ);
                    float biomeValue = GetBiomeValue(globalX, globalZ);

                    int height = heightValue * config::CHUNK_HEIGHT_TO_GENERATE;

                    for (int y = 0; y < config::CHUNK_HEIGHT; ++y) {
                        Block block;

                        if (y <= height) {
                            int dirtAppearingHeight = 1;
                            int rockAppearingHeight = 3;
                            if (y <= config::WATER_LEVEL + 2 * biomeValue) {
                                block = Block(Block::SAND);
                                dirtAppearingHeight = 3;
                                rockAppearingHeight = 5;
                            } else {
                                if (biomeValue < 0.3) {
                                    block = Block(Block::SAND);
                                    dirtAppearingHeight = 3;
                                    rockAppearingHeight = 5;
                                } else if (biomeValue > 0.6 && heightValue > 0.4) {
                                    block = Block(Block::ROCK);
                                    dirtAppearingHeight = config::CHUNK_HEIGHT; // so that it doesn't appear
                                    rockAppearingHeight = 5;
                                    if(heightValue > 0.48) block = Block(Block::FULL_SNOW);
                                    else if(heightValue >= 0.45 && y == height) block = Block(Block::SNOW);
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

void World::GenerateVegetation() {
    for (int i = config::WORLD_MIN_X; i <= config::WORLD_MAX_X; ++i) {
        for (int j = config::WORLD_MIN_Z; j <= config::WORLD_MAX_Z; ++j) {
            std::shared_ptr<Chunk> chunk = GetChunk(i, j);

            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                    int globalX = i * config::CHUNK_SIZE + x;
                    int globalZ = j * config::CHUNK_SIZE + z;

                    float heightValue = GetHeightValue(globalX, globalZ);
                    float biomeValue = GetBiomeValue(globalX, globalZ);

                    int y = heightValue * config::CHUNK_HEIGHT_TO_GENERATE + 1;

                    if(y > config::WATER_LEVEL){
                        if(biomeValue < 0.3 && chunk->GetBlock(x, y - 1, z).GetType() == Block::SAND) {
                            if (rand() % 100 < 1) {
                                World::GenerateCactus(chunk, x, y, z);
                            }
                        }
                        else if(biomeValue > 0.8 && heightValue > 0.8){
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
            auto block = Block(Block::LEAF);
            if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
                chunk->SetBlock(x + xoff, Y, z + zoff, block);
            }
        }
        Y++;
    }

    for(const auto& offset : leafOffsets2){
        int xoff = offset.first;
        int zoff = offset.second;
        auto block = Block(Block::LEAF);
        if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
            chunk->SetBlock(x + xoff, Y, z + zoff, block);
        }
    }

    Y++;

    for(const auto& offset : leafOffsets3){
        int xoff = offset.first;
        int zoff = offset.second;
        auto block = Block(Block::LEAF);
        if(chunk->GetBlock(x + xoff, Y, z + zoff).GetType() == Block::AIR){
            chunk->SetBlock(x + xoff, Y, z + zoff, block);
        }
    }
}

World::World() : perlinHeight(static_cast<unsigned int>(std::time(nullptr))), perlinBiome(std::rand()) {
    GenerateTerrain();
    GenerateVegetation();
}