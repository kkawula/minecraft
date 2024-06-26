#include "ChunkMeshGenerator.h"

#include <glm/glm.hpp>

ChunkMeshGenerator::ChunkMeshGenerator(World& world, MeshAtlas& atlas) {
    this->world = &world;
    this->atlas = &atlas;
}

void ChunkMeshGenerator::setupMesh(int chunkX, int chunkZ) {
    int i = chunkX;
    int j = chunkZ;
    auto chunk = world->GetChunk(i, j);
    auto blocks = chunk->GetBlocks();
    vert.clear();
    for (int x = 0; x < config::CHUNK_SIZE; ++x) {
        for (int y = 0; y < config::CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < config::CHUNK_SIZE; ++z) {
                const Block& block = blocks[x][y][z];
                int selfType = block.GetType();
                if (selfType == Block::AIR) continue;

                checkAndAddFace(i, j, x, y, z, blocks, vert,  0, selfType);
                checkAndAddFace(i, j, x, y, z, blocks, vert,  1, selfType);
                checkAndAddFace(i, j, x, y, z, blocks, vert, 2, selfType);
                checkAndAddFace(i, j, x, y, z, blocks, vert,  3, selfType);
                checkAndAddFace(i, j, x, y, z, blocks, vert, 4, selfType);
                checkAndAddFace(i, j, x, y, z, blocks, vert,5, selfType);
            }
        }
    }
    atlas->chunkMeshes[std::make_pair(i, j)].get()->setupMesh(vert);
}

void ChunkMeshGenerator::checkAndAddFace(int chunkX, int chunkZ, int x, int y, int z, Block blocks[config::CHUNK_SIZE][config::CHUNK_HEIGHT][config::CHUNK_SIZE], std::vector<float>& vert, int face, int selfType) {
    int vectors[6][3] = {
            {-1, 0, 0}, // Left face
            {1, 0, 0}, // Right face
            {0, -1, 0}, // Bottom face
            {0, 1, 0}, // Top face
            {0, 0, -1}, // Back face
            {0, 0, 1}  // Front face
    };
    int dx = vectors[face][0];
    int dy = vectors[face][1];
    int dz = vectors[face][2];

    int nx = x + dx;
    int ny = y + dy;
    int nz = z + dz;
    Block* neighbor = nullptr;

    if (nx >= 0 && nx < config::CHUNK_SIZE && ny >= 0 && ny < config::CHUNK_HEIGHT && nz >= 0 && nz < config::CHUNK_SIZE) {
        neighbor = &blocks[nx][ny][nz];
    } else {
        if (not world->isChunkGenerated(chunkX * config::CHUNK_SIZE + nx, ny, chunkZ * config::CHUNK_SIZE + nz) or ny < 0 or ny >= config::CHUNK_HEIGHT)
            return;

        neighbor = &world->getBlock(chunkX * config::CHUNK_SIZE + nx, ny, chunkZ * config::CHUNK_SIZE + nz);
    }

    bool shouldAdd = false;

    if(neighbor->IsTransparent()) {
        if(selfType == Block::WATER) {
            if(neighbor->GetType() != Block::WATER) {
                shouldAdd = true;
            } else {
                shouldAdd = false;
            }
        } else {
            shouldAdd = true;
        }
    }

    // TODO: implement it as an X-RAY on keybind, currently working all the time
    //if(selfType == Block::COAL_VEIN || selfType == Block::IRON_VEIN || selfType == Block::EMERALD_VEIN || selfType == Block::DIAMOND_VEIN)
    //    addFaceVertices(vert, x, y, z, blocks[x][y][z], face);

    if(shouldAdd) {
        addFaceVertices(vert, x, y, z, blocks[x][y][z], face);
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