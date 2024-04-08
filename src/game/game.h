#ifndef GAME_H
#define GAME_H

#include "../window/WindowState.h"

class Window;

class Game : public WindowState {
public:
    Game(Window* window);
    void update() override;
    void render() override;

private:
    Window* window;
};

#endif // GAME_H
