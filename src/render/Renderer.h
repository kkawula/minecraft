#ifndef MINECRAFT_RENDERER_H
#define MINECRAFT_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../utils/Shader.h"
#include "../utils/Texture.h"
#include "../world/World.h"
#include "../Camera.h"

#include "ChunkRenderer.h"



class Renderer {
private:
    Shader shader;
    Texture texture;
    World* world;

    std::unique_ptr<ChunkRenderer> chunkRenderer;

public:
    Renderer(World& world, const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath);

    void Render(Camera& camera);
};

#endif
