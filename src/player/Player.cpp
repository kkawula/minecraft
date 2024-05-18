#include "Player.h"
#include "GLFW/glfw3.h"

const float GRAVITY = 50.0f;
const float JUMP_ACCELERATION  = 12.0f;
const float DAMPING_FACTOR = 25.0f;

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::update(Keyboard keyboard, Camera &camera, World &world, GLfloat deltaTime) {
    this->acceleration = glm::vec3(0.0f);
    keyboardInput(keyboard, camera);

    if (!isFlying) {
        if (!isOnGround) {
            velocity.y -= GRAVITY * deltaTime;
        }
        isOnGround = false;
    }

    if (glm::length(acceleration) > 0)
        acceleration = glm::normalize(acceleration);

    this->velocity += acceleration * this->movementSpeed * speedMultiplier * deltaTime;

    float maxSpeed = PLAYER_SPEED * 2;
    if (glm::length(this->velocity) > maxSpeed) {
        this->velocity = glm::normalize(this->velocity) * maxSpeed;
    }

    if (position.y <= 0 && !isFlying) {
        position.y = 256;
    }

    position.x += velocity.x * deltaTime;
    collide(world, {velocity.x, 0, 0});

    position.y += velocity.y * deltaTime;
    collide(world, {0, velocity.y, 0});

    position.z += velocity.z * deltaTime;
    collide(world, {0, 0, velocity.z});

    glm::vec3 cameraPosition = {position.x - .5, position.y + box.dimensions.y, position.z - .5};
    camera.setPosition(cameraPosition);

    box.update(position);

    float damping = std::exp(-DAMPING_FACTOR * deltaTime);
    velocity.x *= damping;
    if (isFlying) {
        velocity.y *= damping;
    }
    velocity.z *= damping;
}

void Player::collide(World &world, const glm::vec3 &vel){
    for (int x = position.x - box.dimensions.x;
         x < position.x + box.dimensions.x; x++)
        for (int y = position.y - box.dimensions.y; y < position.y + 0.7; y++)
            for (int z = position.z - box.dimensions.z;
                 z < position.z + box.dimensions.z; z++) {
                auto block = world.getBlock(x, y, z);

                if (block.IsSolid()) {
                    if (vel.y > 0) {
                        position.y = y - box.dimensions.y + .29; //should be .3 but something is messed up
                        velocity.y = 0;
                    }
                    else if (vel.y < 0) {
                        isOnGround = true;
                        position.y = y + box.dimensions.y + 1;
                        velocity.y = 0;
                    }

                    if (vel.x > 0) {
                        position.x = x - box.dimensions.x;
                    }
                    else if (vel.x < 0) {
                        position.x = x + box.dimensions.x + 1;
                    }

                    if (vel.z > 0) {
                        position.z = z - box.dimensions.z;
                    }
                    else if (vel.z < 0) {
                        position.z = z + box.dimensions.z + 1;
                    }
                }
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

void Player::keyboardInput(Keyboard &keyboard, Camera &camera)
{
    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();
    glm::vec3 worldUp = camera.getWorldUp();

    if(keyboard.isKeyPressed(GLFW_KEY_LEFT_ALT))
    {
        isFlying = !isFlying;
        if(isFlying) velocity = glm::vec3(.0f);
    }

    if(isFlying)
    {
        speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 20.0f : 10.0f;
        if (keyboard.isKeyDown(GLFW_KEY_W))
            acceleration += front;

        if (keyboard.isKeyDown(GLFW_KEY_S))
            acceleration -= front;

        if (keyboard.isKeyDown(GLFW_KEY_A))
            acceleration -= right;

        if (keyboard.isKeyDown(GLFW_KEY_D))
            acceleration += right;

        if (keyboard.isKeyDown(GLFW_KEY_SPACE))
            acceleration += worldUp;

        if (keyboard.isKeyDown(GLFW_KEY_LEFT_CONTROL))
            acceleration -= worldUp;
    }

    else
    {
        speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 1.5f : 1.0f;
        glm::vec3 horizontalFront = front;
        horizontalFront.y = 0;
        horizontalFront = glm::normalize(horizontalFront);

        if (keyboard.isKeyDown(GLFW_KEY_W))
            acceleration += horizontalFront;

        if (keyboard.isKeyDown(GLFW_KEY_S))
            acceleration -= horizontalFront;

        if (keyboard.isKeyDown(GLFW_KEY_A))
            acceleration -= right;

        if (keyboard.isKeyDown(GLFW_KEY_D))
            acceleration += right;

        if (keyboard.isKeyDown(GLFW_KEY_SPACE) && isOnGround)
            jump();
    }
}

void Player::jump()
{
    if (isOnGround)
    {
        isOnGround = false;
        velocity.y += JUMP_ACCELERATION;
    }
}