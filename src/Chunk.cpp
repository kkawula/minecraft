#include "Chunk.h"
#include <cstdlib>

float noise(float value) {
    return (float)(rand() % 2001 - 1000) / 1000.0f;
}

Chunk::Chunk() {
    float noiseValues[CHUNK_SIZE][CHUNK_SIZE];

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            noiseValues[x][z] = noise(x * 10 + z * 10);
        }
    }

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                int blockHeight = static_cast<int>((noiseValues[x][z] + 1.0f) / 2.0f * CHUNK_HEIGHT);

                if (y <= blockHeight) {
                    blocks[x][y][z] = Block(6);
                } else {
                    blocks[x][y][z] = Block(0, false);
                }
            }
        }
    }
}
