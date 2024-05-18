#ifndef MINECRAFT_KEYBOARD_H
#define MINECRAFT_KEYBOARD_H

#include <array>
#include "GLFW/glfw3.h"

class Keyboard {
public:
    Keyboard();

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
    bool isKeyDown(int key) ;
    bool isKeyPressed(int key);

private:
    static std::array<bool, 1024> keys;
    static std::array<bool, 1024> keysPressed;
};

#endif //MINECRAFT_KEYBOARD_H