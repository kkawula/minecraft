#ifndef MINECRAFT_CHUNKRENDERER_H
#define MINECRAFT_CHUNKRENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/Shader.h"
#include "../utils/Texture.h"
#include "../world/World.h"
#include "../Camera.h"
#include "../mesh/MeshAtlas.h"


class ChunkRenderer {
private:
    Shader shader;
    Texture texture;
    MeshAtlas* atlas;


public:
    ChunkRenderer(MeshAtlas& atlas);

    void Render(Camera& camera);
};

#endif //MINECRAFT_CHUNKRENDERER_H
