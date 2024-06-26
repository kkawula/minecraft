#ifndef MINECRAFT_BLOCK_H
#define MINECRAFT_BLOCK_H

#include <array>
#include <unordered_map>
#include <iostream>

class Block {
private:
    bool isSolid;
    bool isTransparent;
    bool isCollidable;
    int type;

    struct BlockProperties {
        bool isSolid;
        bool isTransparent;
        bool isCollidable;
    };

    static std::unordered_map<int, std::array<int, 6>> blockTextureIndices;
    static std::unordered_map<int, BlockProperties> blockProperties;

public:
    static constexpr int AIR = 0;
    static constexpr int DIRT = 1;
    static constexpr int GRASS = 2;
    static constexpr int SAND = 3;
    static constexpr int GRAVEL = 4;
    static constexpr int ROCK = 5;
    static constexpr int OAK_WOOD = 6;
    static constexpr int OAK_PLANKS = 7;
    static constexpr int BIRCH_WOOD = 8;
    static constexpr int BIRCH_PLANKS = 9;
    static constexpr int LEAF = 10;
    static constexpr int CACTUS = 11;
    static constexpr int SNOW = 12;
    static constexpr int FULL_SNOW = 13;
    static constexpr int WATERMELON = 14;
    static constexpr int PUMPKIN = 15;
    static constexpr int COAL_VEIN = 16;
    static constexpr int IRON_VEIN = 17;
    static constexpr int EMERALD_VEIN = 18;
    static constexpr int DIAMOND_VEIN = 19;
    static constexpr int BEDROCK = 20;
    static constexpr int BRICK = 21;
    static constexpr int WATER = 22;

    static constexpr int blockTypesAmount = 23;

    Block(int type = 0) : type(type) {
        auto properties = blockProperties[type];
        isSolid = properties.isSolid;
        isTransparent = properties.isTransparent;
        isCollidable = properties.isCollidable;
    }

    bool IsSolid() const {
        return isSolid;
    }

    bool IsTransparent() const {
        return isTransparent;
    }

    int GetType() const {
        return type;
    }

    bool IsCollidable() const {
        return isCollidable;
    }

    static std::array<int, 6> GetTextureIndices(int blockType);
};

#endif //MINECRAFT_BLOCK_H
