#include "World.h"

World::World() {
//    for (int x = -1; x <= 1; ++x) {
//        for (int z = -1; z <= 1; ++z) {
//            chunks[std::make_pair(x, z)] = Chunk();
//        }
//    }
//    chunks[std::make_pair(0, 0)] = Chunk();
    chunks[std::make_pair(-1, -2)] = Chunk();
}
