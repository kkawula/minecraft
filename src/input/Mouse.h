#ifndef MINECRAFT_MOUSE_H
#define MINECRAFT_MOUSE_H

#include <array>

#include "GLFW/glfw3.h"

class Mouse {
public:
    Mouse();

    static void buttonCallback(GLFWwindow *window, int button, int action, int mods);
    bool isButtonDown(int button);
    bool isButtonPressed(int button);

private:
    static std::array<bool, 1024> buttons;
    static std::array<bool, 1024> buttonsPressed;
};


#endif //MINECRAFT_MOUSE_H
