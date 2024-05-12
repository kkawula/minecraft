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

std::string FileSystem::getVertexShaderPath() {
    return (shaderDir / "vert.glsl").string();
}

std::string FileSystem::getFragmentShaderPath() {
    return (shaderDir / "frag.glsl").string();
}

std::string FileSystem::getTexturePath() {
    return (textureDir / "blockPack.png").string();
}

