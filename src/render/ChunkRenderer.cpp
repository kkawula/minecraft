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

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)16/9, 0.1f, 1000.0f);
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
}