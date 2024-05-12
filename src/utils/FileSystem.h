#ifndef MINECRAFT_FILESYSTEM_H
#define MINECRAFT_FILESYSTEM_H

#include <filesystem>

class FileSystem {
private:
    static std::filesystem::path basePath;
    static std::filesystem::path shaderDir;
    static std::filesystem::path textureDir;

public:
    static void initialize(const std::filesystem::path& execPath);

    static std::string getVertexShaderPath();

    static std::string getFragmentShaderPath();

    static std::string getTexturePath();
};


#endif //MINECRAFT_FILESYSTEM_H
