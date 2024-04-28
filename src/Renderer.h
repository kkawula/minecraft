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


class Renderer {
private:
    Shader shader;
    Texture texture;
    GLuint VAO, VBO;

public:
    Renderer(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath);
    ~Renderer();

    void Render(const World& world, const glm::mat4& view, const glm::mat4& projection);
    void SetupMesh();
};

#endif


#endif //MINECRAFT_RENDERER_H
