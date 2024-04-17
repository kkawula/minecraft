#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "../window/window_state.h"

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
