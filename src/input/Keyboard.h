#ifndef MINECRAFT_KEYBOARD_H
#define MINECRAFT_KEYBOARD_H

#include <array>
#include "GLFW/glfw3.h"

class Keyboard {
public:
    Keyboard();

    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

    bool isKeyDown(int key) const;
    bool keyReleased(int key) const;

private:
    std::array<bool, 1024> keys;
    int recentlyReleased;
};

#endif //MINECRAFT_KEYBOARD_H