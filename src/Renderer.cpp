#include "Renderer.h"

Renderer::Renderer(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath)
        : shader(vertexPath, fragmentPath), texture(texturePath) {
    SetupMesh();
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::SetupMesh() {
    GLfloat vertices[] = {
            // positions         // texture coords
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::Render(const World& world, const glm::mat4& view, const glm::mat4& projection) {
    shader.Use();
    texture.Bind();

    shader.SetMat4("projection", projection);
    shader.SetMat4("view", view);

    glBindVertexArray(VAO);

    // Assuming we're just rendering a simple cube for each block for demonstration
    for (const auto& chunk : world.GetChunks()) {
        for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
            for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y) {
                for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                    const Block& block = chunk.second.GetBlock(x, y, z);
                    if (!block.IsSolid()) continue;

                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
                    shader.SetMat4("model", model);

                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                }
            }
        }
    }

    glBindVertexArray(0);
    texture.Unbind();
}
