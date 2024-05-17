#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Entity.h"
#include "../world/World.h"
#include "../Camera.h"
#include "../input/Keyboard.h"

const GLfloat PLAYER_SPEED = 10.0f;
const GLfloat PLAYER_SENSITIVITY = 0.25f;

class Player : public Entity {
public:
    explicit Player(const glm::vec3 &pos);
    void handleInput(Keyboard keyboard, Camera &camera, World &world, GLfloat deltaTime);
    void handleMouseMovement(Camera &camera, GLfloat xOffset, GLfloat yOffset);
    void handleMouseScroll(Camera &camera, GLfloat yOffset);

private:
    bool isOnGround = false;
    bool isFlying = true;

    glm::vec3 acceleration;
    GLfloat movementSpeed = PLAYER_SPEED;
    GLfloat mouseSensitivity = PLAYER_SENSITIVITY;

    std::tuple<bool, glm::vec3> CheckCollision(World &world, glm::vec3 newPosition);
    glm::vec3 ResolveCollision(glm::vec3 desiredMove, glm::vec3 collisionNormal);
};

#endif // PLAYER_H_INCLUDED