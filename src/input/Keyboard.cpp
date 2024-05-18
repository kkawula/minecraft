#include "Keyboard.h"

std::array<bool, 1024> Keyboard::keys = {false};
std::array<bool, 1024> Keyboard::keysPressed = {false};

Keyboard::Keyboard()
{
    std::fill(keys.begin(), keys.end(), false);
    std::fill(keysPressed.begin(), keysPressed.end(), false);
}

void Keyboard::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if ( key >= 0 && key < 1024 )
    {
        if( action == GLFW_PRESS )
        {
            keys[key] = true;
            keysPressed[key] = true;
        }
        else if( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

bool Keyboard::isKeyDown(int key)
{
    return keys[key];
}

bool Keyboard::isKeyPressed(int key)
{
    if(keysPressed[key])
    {
        keysPressed[key] = false;
        return true;
    }
    return false;
}