#include "Chunk.h"
#include <ctime>
#include <cstdlib>

Chunk::Chunk(){
    srand( (unsigned)time(NULL) );

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                blocks[x][y][z] = Block(rand() % 10);
            }
        }
    }
}
