#include "Player.h"
#include "GLFW/glfw3.h"

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::handleInput(Keyboard keyboard, Camera &camera, World &world, GLfloat deltaTime)
{
    GLfloat speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 2.0f : 1.0f;
    GLfloat velocity = this->movementSpeed * deltaTime * speedMultiplier;

    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();
    glm::vec3 worldUp = camera.getWorldUp();

    glm::vec3 newPosition = this->position;

    if (keyboard.isKeyDown(GLFW_KEY_W))
        newPosition += front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_S))
        newPosition -= front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_A))
        newPosition -= right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_D))
        newPosition += right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_SPACE))
        newPosition += worldUp * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_LEFT_CONTROL))
        newPosition -= worldUp * velocity;

    if (!CheckCollision(world, newPosition)) {
        this->position = newPosition;
        camera.setPosition(this->position);
    }
}

void Player::handleMouseMovement(Camera &camera, GLfloat xOffset, GLfloat yOffset)
{
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void Player::handleMouseScroll(Camera &camera, GLfloat yOffset)
{
    camera.ProcessMouseScroll(yOffset);
}

bool Player::CheckCollision(World &world, glm::vec3 newPosition) {
    // Check 3 points: bottom, middle, top (depending on player height)
    glm::vec3 bottom = newPosition - glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 middle = newPosition;
    glm::vec3 top = newPosition + glm::vec3(0.0f, 1.0f, 0.0f);

    return world.getBlock(bottom.x, bottom.y, bottom.z).IsSolid() ||
           world.getBlock(middle.x, middle.y, middle.z).IsSolid() ||
           world.getBlock(top.x, top.y, top.z).IsSolid();
}