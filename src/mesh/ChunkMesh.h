#ifndef MINECRAFT_CHUNKMESH_H
#define MINECRAFT_CHUNKMESH_H

#include <GL/glew.h>
#include <vector>
#include "../world/Block.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../config.h"

class ChunkMesh {
    ChunkMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    ~ChunkMesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Draw() const;


    unsigned int VAO, VBO;
    unsigned int vertexCount = 0;
    void setupMesh();
};


#endif //MINECRAFT_CHUNKMESH_H
