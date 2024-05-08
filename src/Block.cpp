#include "Block.h"

std::unordered_map<int, std::array<int, 6>> Block::blockTextureIndices = {
        {Block::DIRT,  {2,2,2,2,2,2}},
        {Block::GRASS, {1,1,2,0,1,1}},
        {Block::SAND,  {7,7,7,7,7,7}},
        {Block::ROCK,  {3,3,3,3,3,3}},
        {Block::WATER, {8,8,8,8,8,8}},
        {Block::WOOD,  {4,4,5,5,4,4}}
};

std::array<int, 6> Block::GetTextureIndices(int blockType) {
    auto it = blockTextureIndices.find(blockType);
    if (it != blockTextureIndices.end()) {
        return it->second;
    }

    return {};
}