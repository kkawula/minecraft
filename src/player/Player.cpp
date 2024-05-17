#include "Player.h"
#include "GLFW/glfw3.h"

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::handleInput(bool keys[1024])
{
    keyboardInput(keys);

    if (keys[GLFW_KEY_LEFT_ALT]) {
        isFlying = !isFlying;
    }

    if(isFlying) std::cout << "Flying\n";
}

void Player::update(float dt, World &world)
{
    velocity += acceleration;
    acceleration = {0, 0, 0};

    if (!isFlying) {
        if (!isOnGround) {
            velocity.y -= 40 * dt;
        }
        isOnGround = false;
    }

    if (position.y <= 0 && !isFlying) {
        position.y = 300;
    }

    position.x += velocity.x * dt;
    collide(world, {velocity.x, 0, 0}, dt);

    position.y += velocity.y * dt;
    collide(world, {0, velocity.y, 0}, dt);

    position.z += velocity.z * dt;
    collide(world, {0, 0, velocity.z}, dt);

    box.update(position);
    velocity.x *= 0.95f;
    velocity.z *= 0.95f;

    if (isFlying) {
        velocity.y *= 0.95f;
    }

    //std::cout << position.x << " " << position.y << " " << position.z << "\n";
}

void Player::changeFlightMode(){
    std::cout << "Changed flying mode\n";
    isFlying = !isFlying;
}

void Player::collide(World &world, const glm::vec3 &vel, float dt)
{
    for (int x = position.x - box.dimensions.x;
         x < position.x + box.dimensions.x; x++)
        for (int y = position.y - box.dimensions.y; y < position.y + 0.7; y++)
            for (int z = position.z - box.dimensions.z;
                 z < position.z + box.dimensions.z; z++) {
                auto block = world.getBlock(x, y, z);

                if (block.IsCollidable()) {
                    if (vel.y > 0) {
                        position.y = y - box.dimensions.y;
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

float speed = .2f;

void Player::jump()
{
    if (!isFlying) {
        if (isOnGround) {
            isOnGround = false;
            acceleration.y += speed * 50;
        }
    }
    else {
        acceleration.y += speed * 3;
    }
}

void Player::keyboardInput(const bool keys[1024])
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
        float s = speed;
        acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * s;
        acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * s;
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
        acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
        acceleration.x += -glm::cos(glm::radians(rotation.y)) * speed;
        acceleration.z += -glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
        acceleration.x += glm::cos(glm::radians(rotation.y)) * speed;
        acceleration.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    if (keys[GLFW_KEY_SPACE]) {
        jump();
    }
    /*else if (keyboard.isKeyDown(sf::Keyboard::LShift) && m_isFlying) {
        m_acceleration.y -= speed * 3;
    }*/
}