#include "Renderer.h"

Renderer::Renderer(MeshAtlas& atlas)
    : chunkRenderer(atlas) {
    this->atlas = &atlas;

    // Setup some OpenGL options
    glEnable( GL_DEPTH_TEST );

    // enable alpha support
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Renderer::Render(Camera& camera) {
    chunkRenderer.Render(camera);
}