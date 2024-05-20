#include "Mouse.h"

std::array<bool, 1024> Mouse::buttons = {false};
std::array<bool, 1024> Mouse::buttonsPressed = {false};

Mouse::Mouse()
{
    std::fill(buttons.begin(), buttons.end(), false);
    std::fill(buttonsPressed.begin(), buttonsPressed.end(), false);
}

void Mouse::buttonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if(button >= 0 && button < 1024)
    {
        if(action == GLFW_PRESS)
        {
            buttons[button] = true;
            buttonsPressed[button] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            buttons[button] = false;
            buttonsPressed[button] = false;
        }
    }
}

bool Mouse::isButtonDown(int button)
{
    return buttons[button];
}

bool Mouse::isButtonPressed(int button)
{
    if(buttonsPressed[button])
    {
        buttonsPressed[button] = false;
        return true;
    }
    return false;
}