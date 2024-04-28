#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include <map>
#include <utility>

#include "Chunk.h"


class World {
private:
    std::map<std::pair<int, int>, Chunk> chunks;

public:
    World();

    const Chunk& GetChunk(int x, int z) const {
        auto key = std::make_pair(x, z);
        return chunks.at(key);
    }

    auto getChunks() const {
        return chunks;
    }

};


#endif //MINECRAFT_WORLD_H
