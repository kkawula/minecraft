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
    static std::unordered_map<int, std::array<int, 6>> blockTextureIndices;

public:
    static constexpr int AIR = 0;
    static constexpr int DIRT = 1;
    static constexpr int GRASS = 2;
    static constexpr int SAND = 3;
    static constexpr int ROCK = 4;
    static constexpr int WATER = 5;
    static constexpr int OAK_WOOD = 6;
    static constexpr int LEAF = 7;
    static constexpr int CACTUS = 8;
    static constexpr int SNOW = 9;
    static constexpr int FULL_SNOW = 10;
    static constexpr int GRAVEL = 11;
    static constexpr int BIRCH_WOOD = 12;
    static constexpr int WATERMELON = 13;
    static constexpr int PUMPKIN = 14;
    static constexpr int IRON_VEIN = 15;
    static constexpr int DIAMOND_VEIN = 16;
    static constexpr int EMERALD_VEIN = 17;
    static constexpr int COAL_VEIN = 18;
    static constexpr int BEDROCK = 19;
    static constexpr int BRICK = 20;

    static constexpr int blockTypesAmount = 21;


    Block(int type = 0, bool solid = true, bool transparent = false, bool collidable = true) :
        type(type), isSolid(solid), isTransparent(transparent), isCollidable(collidable) {}

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
