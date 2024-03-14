#ifndef MENU_H
#define MENU_H

#include "Button.h"

class Window;

class Menu {
public:
    Menu(Window* window);
    void update();
    void render();
    bool isActive() const;
    bool active = true;
    void handleMouseClick(double xpos, double ypos);

private:
    Window* window;
    Button startButton;
};

#endif
