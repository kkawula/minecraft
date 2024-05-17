#include "FileSystem.h"
#include <iostream>

std::filesystem::path FileSystem::basePath;
std::filesystem::path FileSystem::shaderDir;
std::filesystem::path FileSystem::textureDir;

void FileSystem::initialize(const std::filesystem::path& execPath) {
    basePath = std::filesystem::absolute(execPath).parent_path();
    shaderDir = basePath / "res" / "shaders";
    textureDir = basePath / "res" / "images";
}

std::string FileSystem::getShaderPath(std::string name) {
    return (shaderDir / (name + ".glsl")).string();
}


std::string FileSystem::getTexturePath(std::string name) {
    return (textureDir / (name + ".png")).string();
}

