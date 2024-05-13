#include "Renderer.h"

Renderer::Renderer(MeshAtlas& atlas)
    : chunkRenderer(atlas) {
    this->atlas = &atlas;
}

void Renderer::Render(Camera& camera) {
    chunkRenderer.Render(camera);
}