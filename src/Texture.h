#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
private:
    GLuint textureID;
    int width, height; // Dimensions of the loaded texture
    unsigned char* data; // Raw texture data

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
};

#endif // TEXTURE_H
