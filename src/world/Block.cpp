#include "Block.h"

std::unordered_map<int, std::array<int, 6>> Block::blockTextureIndices = {
        {Block::DIRT,           {2,2,2,2,2,2}},
        {Block::GRASS,          {1,1,2,0,1,1}},
        {Block::SAND,           {6,6,6,6,6,6}},
        {Block::ROCK,           {52,52,52,52,52,52}},
        {Block::WATER,          {7,7,7,7,7,7}},
        {Block::OAK_WOOD,       {16,16,17,17,16,16}},
        {Block::LEAF,           {24,24,24,24,24,24}},
        {Block::CACTUS,         {9,9,8,8,9,9,}},
        {Block::SNOW,           {55,55,52,3,55,55}},
        {Block::FULL_SNOW,      {3,3,3,3,3,3}},
        {Block::GRAVEL,         {5,5,5,5,5,5}},
        {Block::BIRCH_WOOD,     {20,20,21,21,20,20}},
        {Block::WATERMELON,     {33,33,33,32,33,33}},
        {Block::PUMPKIN,        {35,35,35,34,35,35}},
        {Block::IRON_VEIN,      {48,48,48,48,48,48}},
        {Block::DIAMOND_VEIN,   {49,49,49,49,49,49}},
        {Block::EMERALD_VEIN,   {50,50,50,50,50,50}},
        {Block::COAL_VEIN,      {51,51,51,51,51,51}},
        {Block::BEDROCK,        {53,53,53,53,53,53}},
        {Block::BRICK,          {54,54,54,54,54,54}},
};

std::unordered_map<int, Block::BlockProperties> Block::blockProperties = {
        { AIR, { false, true, false } },
        { DIRT, { true, false, true } },
        { GRASS, { true, false, true } },
        { SAND, { true, false, true } },
        { ROCK, { true, false, true } },
        { WATER, { false, true, false } },
        { OAK_WOOD, { true, false, true } },
        { LEAF, { true, false, true } },
        { CACTUS, { true, false, true } },
        { SNOW, { true, false, true } },
        { FULL_SNOW, { true, false, true } },
        { GRAVEL, { true, false, true } },
        { BIRCH_WOOD, { true, false, true } },
        { WATERMELON, { true, false, true } },
        { PUMPKIN, { true, false, true } },
        { IRON_VEIN, { true, false, true } },
        { DIAMOND_VEIN, { true, false, true } },
        { EMERALD_VEIN, { true, false, true } },
        { COAL_VEIN, { true, false, true } },
        { BEDROCK, { true, false, true } },
        { BRICK, { true, false, true } }
};

std::array<int, 6> Block::GetTextureIndices(int blockType) {
    auto it = blockTextureIndices.find(blockType);
    if (it != blockTextureIndices.end()) {
        return it->second;
    }

    return {};
}