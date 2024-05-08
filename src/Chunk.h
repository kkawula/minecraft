#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "Block.h"
#include "Mesh.h"
#include <utility>
#include <iostream>
#include "config.h"

class Chunk {
public:

    Chunk() {
        mesh.setupMesh();
    }


    const Block& GetBlock(int x, int y, int z) const {
        return blocks[x][y][z];
    }

    void SetBlock(int x, int y, int z, const Block& block) {
        blocks[x][y][z] = block;
    }

    void UpdateMesh() {
        mesh.BuildMesh(blocks);
        std::cout<< "Mesh updated" << std::endl;
    }

    void DrawMesh() const {
        mesh.Draw();
    }

private:
    Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE];
    Mesh mesh;
};


#endif //MINECRAFT_CHUNK_H
