#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "Block.h"
#include "../mesh/Mesh.h"
#include <utility>
#include <iostream>
#include "../config.h"

class Chunk {
public:

    const Block& GetBlock(int x, int y, int z) {
        return blocks[x][y][z];
    }

    Block& GetBlock_(int x, int y, int z) {
        return blocks[x][y][z];
    }

    void SetBlock(int x, int y, int z, const Block& block) {
        blocks[x][y][z] = block;
    }

    Block (&GetBlocks())[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE] {
        return blocks;
    }

private:
    Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE];
};


#endif //MINECRAFT_CHUNK_H
