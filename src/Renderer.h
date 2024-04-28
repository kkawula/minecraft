#ifndef MINECRAFT_RENDERER_H
#define MINECRAFT_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "World.h"
#include "Camera.h"


class Renderer {
private:
    Shader shader;
    Texture texture;
    GLuint VAO, VBO;

public:
    Renderer(const GLchar * vertexPath, const GLchar * fragmentPath, const std::string& texturePath);
    ~Renderer();

    void Render( Camera& camera);
    void SetupMesh();
};

#endif