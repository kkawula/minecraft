#include "Player.h"
#include "GLFW/glfw3.h"

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::updatePosition(Camera camera)
{
    this->position = camera.getPosition();
}