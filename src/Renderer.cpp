#include "Renderer.h"
#include "config.h"

Renderer::Renderer(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath)
        : shader(vertexPath, fragmentPath), texture(texturePath) {
    SetupMesh();
}

Renderer::~Renderer() {
}

void Renderer::SetupMesh() {
}

void Renderer::Render(World &world, Camera& camera) {
    shader.Use();
    texture.Bind();

    texture.Bind(0);  // Bind to texture unit 0
    glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)config::WINDOW_WIDTH / (GLfloat)config::WINDOW_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    GLint viewLoc = glGetUniformLocation(shader.Program, "view");
    GLint projLoc = glGetUniformLocation(shader.Program, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    for (int i = 0; i < config::WORLD_SIZE; ++i) {
        for (int j = 0; j < config::WORLD_SIZE; ++j) {
            std::shared_ptr<Chunk> chunk = world.GetChunk(i, j);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i * config::CHUNK_SIZE, 1, j * config::CHUNK_SIZE));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            chunk.get()->DrawMesh();
        }
    }


    texture.Unbind();
}
