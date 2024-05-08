#ifndef MINECRAFT_MESH_H
#define MINECRAFT_MESH_H

#include <GL/glew.h>
#include <vector>
#include "Block.h"
#include <glm/glm.hpp>
#include <iostream>
#include "config.h"

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

    void BuildMesh(const Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE]);
    void Draw() const;

    void addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face);

    std::vector<float> vertices;
    unsigned int VAO, VBO;
    void setupMesh();
};

#endif //MINECRAFT_MESH_H
