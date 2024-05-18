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

    static std::string getShaderPath(std::string name);
    static std::string getTexturePath(std::string name);
};


#endif //MINECRAFT_FILESYSTEM_H
