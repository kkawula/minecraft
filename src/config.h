#ifndef MINECRAFT_CONFIG_H
#define MINECRAFT_CONFIG_H

namespace config {
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 256;
    static constexpr int CHUNK_HEIGHT_TO_GENERATE = 150;
    static constexpr int BASE_HEIGHT = 50;


    static constexpr int VIEW_RADIUS = 50;

    static constexpr int BIOME_OCTAVE = 3;
    static constexpr int WATER_LEVEL = BASE_HEIGHT + 10;

    static constexpr int WINDOW_WIDTH = 1000;
    static constexpr int WINDOW_HEIGHT = 750;
}

#endif //MINECRAFT_CONFIG_H
