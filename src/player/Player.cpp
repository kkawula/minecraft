#include "Player.h"
#include "GLFW/glfw3.h"

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::handleInput(Keyboard keyboard, Camera &camera, GLfloat deltaTime)
{
    GLfloat speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 2.0f : 1.0f;
    GLfloat velocity = this->movementSpeed * deltaTime * speedMultiplier;

    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();
    glm::vec3 worldUp = camera.getWorldUp();

    if (keyboard.isKeyDown(GLFW_KEY_W))
        this->position += front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_S))
        this->position -= front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_A))
        this->position -= right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_D))
        this->position += right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_SPACE))
        this->position += worldUp * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_LEFT_CONTROL))
        this->position -= worldUp * velocity;

    camera.setPosition(this->position);
}

void Player::handleMouseMovement(Camera &camera, GLfloat xOffset, GLfloat yOffset)
{
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void Player::handleMouseScroll(Camera &camera, GLfloat yOffset)
{
    camera.ProcessMouseScroll(yOffset);
}