#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H
#include <GLFW/glfw3.h>


class Window {
public:
    GLFWwindow* window;
    const unsigned int width;
    const unsigned int height;
    const char* title;

    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
    bool ShouldClose();
    void swapBuffers();

    void setKeyCallback(GLFWkeyfun callback);
    void setCursorPosCallback(GLFWcursorposfun callback);
    void setScrollCallback(GLFWscrollfun callback);
    void setMouseButtonCallback(GLFWmousebuttonfun callback);
};


#endif //MINECRAFT_WINDOW_H
