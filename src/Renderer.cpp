#include "Renderer.h"

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

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)800 / (GLfloat)600, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    GLint viewLoc = glGetUniformLocation(shader.Program, "view");
    GLint projLoc = glGetUniformLocation(shader.Program, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            std::shared_ptr<Chunk> chunk = world.GetChunk(i, j);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i*16, 1, j*16));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            chunk.get()->DrawMesh();
        }
    }


    texture.Unbind();
}
