#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "../menu/Menu.h"
#include "../Game/Game.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    void run();
    Menu& getMenu();
    GLFWwindow* getGLFWwindow();

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

private:
    GLFWwindow* window;
    Menu menu;
};

#endif
