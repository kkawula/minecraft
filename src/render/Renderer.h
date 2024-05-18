#ifndef MINECRAFT_RENDERER_H
#define MINECRAFT_RENDERER_H

#include "../Camera.h"
#include "../mesh/MeshAtlas.h"
#include "ChunkRenderer.h"

class Renderer {
private:
    MeshAtlas* atlas;
    ChunkRenderer chunkRenderer;

public:
    Renderer(MeshAtlas& atlas);
    void Render(Camera& camera);
};

#endif
