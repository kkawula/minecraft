#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "Block.h"
#include <utility>

class Chunk {
public:
    static const int CHUNK_SIZE = 16;
    static const int CHUNK_HEIGHT = 256;

    Chunk() {};

    const Block& GetBlock(int x, int y, int z) const {
        return blocks[x][y][z];
    }

    void SetBlock(int x, int y, int z, const Block& block) {
        blocks[x][y][z] = block;
    }

private:
    Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
};


#endif //MINECRAFT_CHUNK_H
