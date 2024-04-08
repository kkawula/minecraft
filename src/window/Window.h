#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "../menu/menu.h"
#include "../game/game.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    void run();
    void changeToMenu();
    void changeToGame();

    int getWidth();
    int getHeight();
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    GLFWwindow* getWindow();

private:
    GLFWwindow* window;
    WindowState* currentState;
    Menu menu;
    Game game;
};

#endif
