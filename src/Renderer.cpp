#include "Renderer.h"

Renderer::Renderer(const GLchar *vertexPath, const GLchar *fragmentPath, const std::string& texturePath)
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
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    //back
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    //left
                    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

                    // right
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    // bottom
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    // top
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };


//    VertexArray va; moved to constructor
    VertexBuffer vb(vertices, sizeof(vertices));

    va.Bind();
    vb.Bind();

    va.AddBuffer(vb, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    va.AddBuffer(vb, 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    va.Unbind();
    vb.Unbind();
}

void Renderer::Render( Camera& camera) {
    shader.Use();
    texture.Bind();

    glm::vec3 cubePositions[] =
            {
                    glm::vec3( 0.0f, 0.0f, 0.0f ),
                    glm::vec3( 2.0f, 5.0f, -15.0f ),
                    glm::vec3( -1.5f, -2.2f, -2.5f ),
                    glm::vec3( -3.8f, -2.0f, -12.3f ),
                    glm::vec3( 2.4f, -0.4f, -3.5f ),
                    glm::vec3( -1.7f, 3.0f, -7.5f ),
                    glm::vec3( 1.3f, -2.0f, -2.5f ),
                    glm::vec3( 1.5f, 2.0f, -2.5f ),
                    glm::vec3( 1.5f, 0.2f, -1.5f ),
                    glm::vec3( -1.3, 1.0f, -1.5f )
            };
    // Bind Texture using the texture class
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
    for (GLuint i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        GLfloat angle = 20.0f * 0;  // This seems like it was meant to be dynamic
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    texture.Unbind();
}
