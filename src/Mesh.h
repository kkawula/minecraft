#ifndef MINECRAFT_MESH_H
#define MINECRAFT_MESH_H

#include <GL/glew.h>
#include <vector>
#include "Block.h"
#include <glm/glm.hpp>
#include <iostream>

class Mesh {
public:
    Mesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        std::cout << "Mesh created" << std::endl;
        std::cout << "VAO: " << VAO << std::endl;
        std::cout << "VBO: " << VBO << std::endl;

    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void BuildMesh(const Block blocks[16][100][16]);
    void Draw() const;

    void addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face);

    int getVerticesSize() const {
        return vertices.size();
    }

    std::vector<float> vertices;
    unsigned int VAO, VBO;
    std::string jajo = "jajo";
    void setupMesh();
};

#endif //MINECRAFT_MESH_H
