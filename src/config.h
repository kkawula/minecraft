#ifndef MINECRAFT_CONFIG_H
#define MINECRAFT_CONFIG_H

namespace config {
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 128;
    static constexpr int CHUNK_HEIGHT_TO_GENERATE = 100;
    static constexpr int WORLD_MIN_X = -2;
    static constexpr int WORLD_MIN_Z = -2;
    static constexpr int WORLD_MAX_X = 0;
    static constexpr int WORLD_MAX_Z = 0;
    static constexpr int WORLD_SIZE = WORLD_MAX_X - WORLD_MIN_X + 1;

    static constexpr int BIOME_OCTAVE = 3;
    static constexpr int WATER_LEVEL = CHUNK_HEIGHT_TO_GENERATE / 3;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
}

#endif //MINECRAFT_CONFIG_H
