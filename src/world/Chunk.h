#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "Block.h"
#include "../mesh/Mesh.h"
#include <utility>
#include <iostream>
#include "../config.h"

class Chunk {
public:

    const Block& GetBlock(int x, int y, int z) const {
        return blocks[x][y][z];
    }

    void SetBlock(int x, int y, int z, const Block& block) {
        blocks[x][y][z] = block;
    }

    void DrawMesh() const {
        mesh.Draw();
    }

    Block (&GetBlocks())[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE] {
        return blocks;
    }

    void setupMesh(const std::vector<float>& vert) {
        mesh.setupMesh(vert);
    }

private:
    Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE];
    Mesh mesh;
};


#endif //MINECRAFT_CHUNK_H
