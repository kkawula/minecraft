#include "ChunkRenderer.h"
#include "../utils/FileSystem.h"

ChunkRenderer::ChunkRenderer(MeshAtlas& atlas) : shader(FileSystem::getShaderPath("block_vert"), FileSystem::getShaderPath("block_frag")), texture(FileSystem::getTexturePath("blockPack")) {
    this->atlas = &atlas;

}

void ChunkRenderer::Render(Camera& camera) {
    shader.Use();
    texture.Bind();

    texture.Bind(0);
    glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)config::WINDOW_WIDTH / (GLfloat)config::WINDOW_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    GLint viewLoc = glGetUniformLocation(shader.Program, "view");
    GLint projLoc = glGetUniformLocation(shader.Program, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    for (auto it = atlas->cords()->begin(); it != atlas->cords()->end(); it++){
        int i = it->first;
        int j = it->second;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i * config::CHUNK_SIZE, 1, j * config::CHUNK_SIZE));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        atlas->chunkMeshes[std::make_pair(i, j)].get()->Draw();
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    float lineVertices[] = {
            0, 100, 0,
            100, 100, 0,
            0, 100, 0,
            0, 100, 100,
            0,100,0,
            0,200,0
    };

    GLuint VAO, VBO;

// Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

// Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

// Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

// Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);

    texture.Unbind();
}