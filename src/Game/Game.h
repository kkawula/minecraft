#ifndef GAME_H
#define GAME_H

class Window;

class Game {
public:
    Game(Window* window);
    void update();
    void render();
    bool isActive() const;

private:
    Window* window;
};

#endif // GAME_H
