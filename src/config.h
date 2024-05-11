#ifndef MINECRAFT_CONFIG_H
#define MINECRAFT_CONFIG_H

namespace config {
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 128;
    static constexpr int CHUNK_HEIGHT_TO_GENERATE = 100;
    static constexpr int WORLD_MIN_X = 0;
    static constexpr int WORLD_MIN_Z = 0;
    static constexpr int WORLD_MAX_X = 20;
    static constexpr int WORLD_MAX_Z = 20;
    static constexpr int WORLD_SIZE = 20;

    static constexpr int BIOME_OCTAVE = 3;
    static constexpr int NOISE_WIDTH = CHUNK_SIZE * WORLD_SIZE;
    static constexpr int NOISE_HEIGHT = CHUNK_SIZE * WORLD_SIZE;
    static constexpr int WATER_LEVEL = CHUNK_HEIGHT_TO_GENERATE / 2.5;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
}

#endif //MINECRAFT_CONFIG_H
