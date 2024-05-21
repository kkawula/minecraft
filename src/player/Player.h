#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Entity.h"
#include "../world/World.h"
#include "../Camera.h"
#include "../input/Keyboard.h"
#include "../input/Mouse.h"

const GLfloat PLAYER_SPEED = 150.0f;

class Player : public Entity {
public:
    explicit Player(const glm::vec3 &pos);
    void update(Keyboard keyboard, Mouse mouse, Camera &camera, World &world, GLfloat deltaTime);
    static void handleMouseMovement(Camera &camera, GLfloat xOffset, GLfloat yOffset);
    static void handleMouseScroll(Camera &camera, GLfloat yOffset);

private:
    bool isOnGround = false;
    bool isFlying = true;

    glm::vec3 acceleration;
    GLfloat movementSpeed = PLAYER_SPEED;
    GLfloat speedMultiplier = 1.0f;

    void collide(World &world, const glm::vec3 &vel);

    void keyboardInput(Keyboard &keyboard, Camera &camera, World &world);
    void mouseInput(Mouse mouse, Camera &camera, World &world);

    void jump();
    void placeBlock(World &world, Camera &camera);
    void dig(World &world, Camera &camera);

    bool isCollidingWithPlayer(const glm::vec3 &blockPosition);
};

#endif // PLAYER_H_INCLUDED