#include <iostream>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

Texture::Texture(const std::string& path)
        : textureID(0), width(0), height(0), data(nullptr) {
    // Load image
    stbi_set_flip_vertically_on_load(0); // Flip the y-axis in loading
    data = stbi_load(path.c_str(), &width, &height, nullptr, 4); // Assuming RGBA for now

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot); // Activate the proper texture unit before binding
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
