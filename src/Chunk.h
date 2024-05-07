#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "Block.h"
#include "Mesh.h"
#include <utility>
#include <iostream>

class Chunk {
public:
    static const int CHUNK_SIZE = 16;
    static const int CHUNK_HEIGHT = 100;

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

    int getVerticesSize() const {
        return mesh.getVerticesSize();
    }

    Mesh& getMesh() {
        return mesh;
    }

private:
    Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    Mesh mesh;
    std::string pomidor = "pomidor";
};


#endif //MINECRAFT_CHUNK_H
