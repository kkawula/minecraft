#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "../window/WindowState.h"

class Window;

class Menu : public WindowState {
public:
    Menu(Window* window);
    void update() override;
    void render() override;
    void handleMouseClick(double xpos, double ypos);

private:
    Window* window;
    Button startButton;
};

#endif
