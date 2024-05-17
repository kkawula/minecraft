#ifndef MINECRAFT_MESHATLAS_H
#define MINECRAFT_MESHATLAS_H

#include <map>
#include <memory>
#include "Mesh.h"
#include "../config.h"
#include <set>

class MeshAtlas {
public:
    MeshAtlas() {}

    bool isMeshGenerated(int x, int z) {
        return chunkMeshes[std::make_pair(x, z)] != nullptr;
    }

    void createEntry(int x, int z) {
        chunkMeshes[std::make_pair(x, z)] = std::make_shared<Mesh>();
    }

    std::set<std::pair<int, int>> *cords() {
        return &_cords;
    };


    std::map<std::pair<int, int>, std::shared_ptr<Mesh>> chunkMeshes;

private:
    std::set<std::pair<int, int>> _cords;

};


#endif //MINECRAFT_MESHATLAS_H
