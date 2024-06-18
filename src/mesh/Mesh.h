#ifndef MINECRAFT_MESH_H
#define MINECRAFT_MESH_H

#include <vector>
#include <iostream>

#include <GL/glew.h>

#include "../world/Block.h"
#include "../config.h"

class Mesh {
public:
    Mesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Draw() const;


    unsigned int VAO, VBO;
    unsigned int vertexCount = 0;
    void setupMesh(const std::vector<float>& vert);
};

#endif //MINECRAFT_MESH_H
