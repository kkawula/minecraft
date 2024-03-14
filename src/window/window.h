#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

private:
    GLFWwindow* window;
};

#endif // WINDOW_H
