#include "ChunkMeshGenerator.h"

#include "../config.h"

ChunkMeshGenerator::ChunkMeshGenerator(World& world) {
    this->world = &world;
}

void ChunkMeshGenerator::setupMeshes() {
    for (int i = config::WORLD_MIN_X; i < config::WORLD_MAX_X; ++i) {
        for (int j = config::WORLD_MIN_Z; j < config::WORLD_MAX_Z; ++j) {
            auto chunk = world->GetChunk(i, j);
            auto blocks = chunk.get()->GetBlocks();
            vert.clear();
            for (int x = 0; x < config::CHUNK_SIZE; ++x) {
                for (int y = 0; y < config::CHUNK_HEIGHT; ++y) {
                    for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                        const Block& block = blocks[x][y][z];
                        if (block.GetType() == Block::AIR) continue;

                        if(block.IsSolid()) {
                            if (x == 0 || !blocks[x - 1][y][z].IsSolid() ||
                                (blocks[x - 1][y][z].IsSolid() && blocks[x - 1][y][z].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 0);
                            }
                            if (x == config::CHUNK_SIZE - 1 || !blocks[x + 1][y][z].IsSolid() ||
                                (blocks[x + 1][y][z].IsSolid() && blocks[x + 1][y][z].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 1);
                            }
                            if (y == 0 || !blocks[x][y - 1][z].IsSolid() ||
                                (blocks[x][y - 1][z].IsSolid() && blocks[x][y - 1][z].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 2);
                            }
                            if (y == config::CHUNK_HEIGHT - 1 || !blocks[x][y + 1][z].IsSolid() ||
                                (blocks[x][y + 1][z].IsSolid() && blocks[x][y + 1][z].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 3);
                            }
                            if (z == 0 || !blocks[x][y][z - 1].IsSolid() ||
                                (blocks[x][y][z - 1].IsSolid() && blocks[x][y][z - 1].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 4);
                            }
                            if (z == config::CHUNK_SIZE - 1 || !blocks[x][y][z + 1].IsSolid() ||
                                (blocks[x][y][z + 1].IsSolid() && blocks[x][y][z + 1].IsTransparent())) {
                                addFaceVertices(vert, x, y, z, block, 5);
                            }
                        }

                        else{ //WATER
                            if(y == config::CHUNK_HEIGHT - 1 || !blocks[x][y + 1][z].IsTransparent() || blocks[x][y + 1][z].GetType() == Block::AIR){
                                addFaceVertices(vert, x, y, z, block, 3);
                            }
                        }
                    }
                }
            }
            std::cout << "Mesh updated "<< vert.size() << std::endl;
            chunk.get()->setupMesh(vert);
        }
    }
}

void ChunkMeshGenerator::addFaceVertices(std::vector<float>& vertices, int x, int y, int z, const Block& block, int face) {
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
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f)
    };


    float tileSize = 1.0 / 16.0;
    int tilesPerRow = 16;

    std::array<int, 6> textureIndices = Block::GetTextureIndices(block.GetType());

    glm::vec2 tileOffset = glm::vec2(textureIndices[face] % tilesPerRow, textureIndices[face] / tilesPerRow) * tileSize;

    for (int i = 0; i < 6; ++i) {
        glm::vec3 vertexPos = glm::vec3(x, y, z) + cubeVertices[faceIndices[face][i]];

        vertices.push_back(vertexPos.x);
        vertices.push_back(vertexPos.y);
        vertices.push_back(vertexPos.z);

        glm::vec2 coord = textureCoords[i % 4] * tileSize + tileOffset;
        vertices.push_back(coord.x);
        vertices.push_back(coord.y);

    }
}