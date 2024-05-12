#ifndef MINECRAFT_MESHATLAS_H
#define MINECRAFT_MESHATLAS_H

#include <map>
#include <memory>
#include "Mesh.h"
#include "../config.h"
class MeshAtlas {
public:
    MeshAtlas() {
        for (int x = config::WORLD_MIN_X; x <= config::WORLD_MAX_X; x++) {
            for (int z = config::WORLD_MIN_Z; z <= config::WORLD_MAX_Z; z++) {
                chunkMeshes[std::make_pair(x, z)] = std::make_shared<Mesh>();
            }
        }
    }

    std::map<std::pair<int, int>, std::shared_ptr<Mesh>> chunkMeshes;
};


#endif //MINECRAFT_MESHATLAS_H
