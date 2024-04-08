#ifndef GAME_H
#define GAME_H

#include "../window/WindowState.h"
#include "./camera.h"

class Window;

class Game : public WindowState {
public:
    Game(Window* window);

    void update() override;
    void render() override;

private:
    Window* window;
    Camera camera;
};

#endif // GAME_H
