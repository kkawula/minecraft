#include "Mesh.h"
#include <iostream>
void Mesh::BuildMesh(const Block blocks[16][100][16]) {
    vertices.clear();
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 100; ++y) {
            for (int z = 0; z < 16; ++z) {
                const Block& block = blocks[x][y][z];
                if (!block.IsSolid()) continue;

                if (x == 0 || !blocks[x - 1][y][z].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 0);
                }
                if (x == 15 || !blocks[x + 1][y][z].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 1);
                }
                if (y == 0 || !blocks[x][y - 1][z].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 2);
                }
                if (y == 99 || !blocks[x][y + 1][z].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 3);
                }
                if (z == 0 || !blocks[x][y][z - 1].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 4);
                }
                if (z == 15 || !blocks[x][y][z + 1].IsSolid()) {
                    addFaceVertices(vertices, x, y, z, block, 5);
                }


            }
        }
    }
    std::cout << "Vertices size: " << this->getVerticesSize() << std::endl;
    setupMesh();
}

void Mesh::setupMesh() {
    std::cout << "VAO binded: " << VAO << std::endl;
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw() const {
    std::cout << "VAO draw: " << VAO << std::endl;

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
    std::cout << vertices.size() << std::endl;
    glBindVertexArray(0);
}

void Mesh::addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face) {
    static const glm::vec3 cubeVertices[8] = {
            glm::vec3(-0.5f, -0.5f, -0.5f), // 0
            glm::vec3(0.5f, -0.5f, -0.5f), // 1
            glm::vec3(0.5f, 0.5f, -0.5f), // 2
            glm::vec3(-0.5f, 0.5f, -0.5f), // 3
            glm::vec3(-0.5f, -0.5f, 0.5f), // 4
            glm::vec3(0.5f, -0.5f, 0.5f), // 5
            glm::vec3(0.5f, 0.5f, 0.5f), // 6
            glm::vec3(-0.5f, 0.5f, 0.5f) // 7
    };

    static const int faceIndices[6][6] = {
            {0, 7, 4, 3, 0, 7}, // Left face
            {1, 6, 5, 2, 1, 6}, // Right face
            {0, 5, 1, 4, 0, 5}, // Bottom face
            {2, 7, 3, 6, 2, 7}, // Top face
            {0, 2, 1, 3, 0, 2}, // Back face
            {4, 6, 5, 7, 4, 6}  // Front face
    };

    // Texture coordinates for each vertex
    static const glm::vec2 textureCoords[4] = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 1.0f)
    };



    for (int i = 0; i < 6; ++i) {
        glm::vec3 vertexPos = glm::vec3(x, y, z) + cubeVertices[faceIndices[face][i]];

        // Append vertex position
        vertices.push_back(vertexPos.x);
        vertices.push_back(vertexPos.y);
        vertices.push_back(vertexPos.z);

        // Append texture coordinates
        vertices.push_back(textureCoords[i % 4].x);
        vertices.push_back(textureCoords[i % 4].y);

    }
}