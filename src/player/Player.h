#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Entity.h"
#include "../world/World.h"
#include "../Camera.h"

class Player : public Entity {
public:
    explicit Player(const glm::vec3 &pos);
    void updatePosition(Camera camera);

private:
    bool isOnGround = false;
    bool isFlying = true;

    glm::vec3 acceleration;
};

#endif // PLAYER_H_INCLUDED