#include "Renderer.h"

Renderer::Renderer(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath)
        : shader(vertexPath, fragmentPath), texture(texturePath) {
    SetupMesh();
}

Renderer::~Renderer() {
}

void Renderer::SetupMesh() {
    GLfloat vertices[] =
        {
            //front
            // x     y     z     u     v
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            //back
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            //left
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

            // right
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            // bottom
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            // top
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        };

    GLuint indicies[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };



//    VertexArray va; moved to constructor
    VertexBuffer vb(vertices, sizeof(vertices));

    va.Bind();
    vb.Bind();

    va.AddBuffer(vb, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    va.AddBuffer(vb, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    va.Unbind();
    vb.Unbind();
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

    // Bind VAO
    va.Bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    /*for (const auto& entry : world.getChunks()) {
        for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
            for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y) {
                for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                    const Block& block = entry.second.GetBlock(x, y, z);
                    //if (!block.IsSolid()) continue;

                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(entry.first.first * Chunk::CHUNK_SIZE + x, y,  entry.first.second * Chunk::CHUNK_SIZE  + z));
//                    GLfloat angle = 20.0f * 0;  // This seems like it was meant to be dynamic
//                    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glUniform1i(glGetUniformLocation(shader.Program, "blockType"), block.GetType());
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
    }*/

    for (const auto& entry : world.getChunks()) {
        for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                for (int y = 0; y < Chunk::CHUNK_HEIGHT; ++y) {
                    const Block& block = entry.second.GetBlock(x, y, z);
                    if (y + 1 < Chunk::CHUNK_HEIGHT && entry.second.GetBlock(x, y + 1, z).IsSolid()) continue;

                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(entry.first.first * Chunk::CHUNK_SIZE + x, y,  entry.first.second * Chunk::CHUNK_SIZE  + z));
//                    GLfloat angle = 20.0f * 0;  // This seems like it was meant to be dynamic
//                    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glUniform1i(glGetUniformLocation(shader.Program, "blockType"), block.GetType());
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    break;
                }
            }
        }
    }

    texture.Unbind();
}
