#ifndef MINECRAFT_BLOCK_H
#define MINECRAFT_BLOCK_H


class Block {
private:
    bool isSolid;
    int type;

public:
    Block(int type = 0, bool solid = true) : type(type), isSolid(solid) {}

    bool IsSolid() const {
        return isSolid;
    }

    int GetType() const {
        return type;
    }
};


#endif //MINECRAFT_BLOCK_H
