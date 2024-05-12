#ifndef MINECRAFT_BLOCK_H
#define MINECRAFT_BLOCK_H

#include <array>
#include <unordered_map>
#include <iostream>

class Block {
private:
    bool isSolid;
    bool isTransparent;
    int type;
    static std::unordered_map<int, std::array<int, 6>> blockTextureIndices;

public:
    static constexpr int AIR = 0;
    static constexpr int DIRT = 1;
    static constexpr int GRASS = 2;
    static constexpr int SAND = 3;
    static constexpr int ROCK = 4;
    static constexpr int WATER = 5;
    static constexpr int WOOD = 6;
    static constexpr int LEAF = 7;
    static constexpr int CACTUS = 8;


    Block(int type = 0, bool solid = true, bool transparent = false) : type(type), isSolid(solid), isTransparent(transparent) {}

    bool IsSolid() const {
        return isSolid;
    }

    bool IsTransparent() const {
        return isTransparent;
    }

    int GetType() const {
        return type;
    }

    static std::array<int, 6> GetTextureIndices(int blockType);
};

#endif //MINECRAFT_BLOCK_H
