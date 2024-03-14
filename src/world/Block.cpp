#ifndef BLOCK_H
#define BLOCK_H

#include "BlockType.h"

class Block {
public:
    Block(BlockType type = BlockType::DIRT) : type(type), active(true) {}

    bool isActive() const { return active; }
    void setActive(bool active) { this->active = active; }

    BlockType getType() const { return type; }
    void setType(BlockType type) { this->type = type; }

private:
    BlockType type;
    bool active;
};

#endif // BLOCK_H
