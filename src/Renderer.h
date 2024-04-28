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
#include "VertexArray.h"
#include "VertexBuffer.h"


class Renderer {
private:
    Shader shader;
    Texture texture;
    VertexArray va;

public:
    Renderer(const GLchar * vertexPath, const GLchar * fragmentPath, const std::string& texturePath);
    ~Renderer();

    void Render(World& world, Camera& camera);
    void SetupMesh();
};

#endif
