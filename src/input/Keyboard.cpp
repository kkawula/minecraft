#include "Keyboard.h"

Keyboard::Keyboard()
{
    std::fill(keys.begin(), keys.end(), false);
}

void Keyboard::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key == GLFW_KEY_SPACE || key == GLFW_KEY_LEFT_CONTROL)
    {
        if( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    if ( key >= 0 && key < 1024 )
    {
        if( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

bool Keyboard::isKeyDown(int key) const
{
    return keys[key];
}

bool Keyboard::keyReleased(int key) const
{
    return recentlyReleased == key;
}