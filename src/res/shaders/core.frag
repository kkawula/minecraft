#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform int blockType; // Uniform to pass the block type

void main() {
    float tileSize = 1.0 / 16.0; // As there are 16x16 tiles in the atlas
    int tilesPerRow = 16; // 16 tiles per row
    int tileX = blockType % tilesPerRow;
    int tileY = blockType / tilesPerRow;

    vec2 tileOffset = vec2(tileX, tileY) * tileSize;
    vec2 coord = TexCoord * tileSize + tileOffset;

    FragColor = texture(ourTexture1, coord);
}