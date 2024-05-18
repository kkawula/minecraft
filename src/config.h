#ifndef MINECRAFT_CONFIG_H
#define MINECRAFT_CONFIG_H

namespace config {
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 256;
    static constexpr int CHUNK_HEIGHT_TO_GENERATE = 200;
  
    static constexpr int WORLD_MIN_X = -15;
    static constexpr int WORLD_MIN_Z = -15;
    static constexpr int WORLD_MAX_X = 15;
    static constexpr int WORLD_MAX_Z = 15;

    static constexpr int VIEW_RADIUS = 10;


    static constexpr int BIOME_OCTAVE = 3;
    static constexpr int WATER_LEVEL = 10;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
}

#endif //MINECRAFT_CONFIG_H
