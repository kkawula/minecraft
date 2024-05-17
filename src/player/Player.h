#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Entity.h"
#include "../world/World.h"

class Player : public Entity {
public:
    Player(const glm::vec3 &pos);

    void handleInput(bool keys[1024]);
    void update(float dt, World &world);
    void collide(World &world, const glm::vec3 &vel, float dt);
    void changeFlightMode();

private:
    void jump();
    bool isOnGround = false;
    bool isFlying = false;

    void keyboardInput(const bool keys[1024]);

    glm::vec3 acceleration;
};

#endif // PLAYER_H_INCLUDED