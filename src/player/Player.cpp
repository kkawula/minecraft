#include "Player.h"
#include "GLFW/glfw3.h"
#include <cmath>

const float GRAVITY = 50.0f;
const float JUMP_ACCELERATION  = 12.0f;
const float DAMPING_FACTOR = 25.0f;

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::update(Keyboard keyboard, Mouse mouse, Camera &camera, World &world, GLfloat deltaTime) {
    this->acceleration = glm::vec3(0.0f);
    keyboardInput(keyboard, camera, world);
    mouseInput(mouse, camera, world);

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
    if(!isFlying) collide(world, {velocity.x, 0, 0});

    position.y += velocity.y * deltaTime;
    if(!isFlying) collide(world, {0, velocity.y, 0});

    position.z += velocity.z * deltaTime;
    if(!isFlying) collide(world, {0, 0, velocity.z});

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
    for (int x = floor(position.x - box.dimensions.x); x < position.x + box.dimensions.x; x++) {
        for (int y = position.y - box.dimensions.y; y < position.y + 0.7; y++) {
            for (int z = floor(position.z - box.dimensions.z); z < position.z + box.dimensions.z; z++) {
                auto block = world.getBlock(x, y, z);

                if (block.IsSolid()) {
                    //@TODO remove this tricky solution (adjusting the numbers), don't know why is it not working without that
                    //Only bugging on chunk edges
                    if (vel.y > 0) {
                        position.y = y - box.dimensions.y + .2999;
                        velocity.y = 0;
                    } else if (vel.y < 0) {
                        isOnGround = true;
                        position.y = y + box.dimensions.y + 1;
                        velocity.y = 0;
                    }

                    if (vel.x > 0) {
                        position.x = x - box.dimensions.x - 0.0001;
                    } else if (vel.x < 0) {
                        position.x = x + box.dimensions.x + 1.0001;
                    }

                    if (vel.z > 0) {
                        position.z = z - box.dimensions.z - 0.0001;
                    } else if (vel.z < 0) {
                        position.z = z + box.dimensions.z + 1.0001;
                    }
                }
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

void Player::keyboardInput(Keyboard &keyboard, Camera &camera, World &world)
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
        speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 20.0f : 2.0f;
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

void Player::mouseInput(Mouse mouse, Camera &camera, World &world)
{
    if(mouse.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        dig(world, camera);
    }

    if(mouse.isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    {
        placeBlock(world, camera);
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

void Player::dig(World &world, Camera &camera)
{
    glm::vec3 front = camera.getFront();
    glm::vec3 rayStep = {front.x * 0.05, front.y * 0.05, front.z * 0.05};
    for(auto rayPos = glm::vec3(0); glm::length(rayPos) < 4; rayPos += rayStep)
    {
        int x = floor(position.x + rayPos.x);
        int y = floor(position.y + .5 + rayPos.y);
        int z = floor(position.z + rayPos.z);
        auto block = world.getBlock(x, y, z);

        if(block.GetType() != Block::AIR && block.GetType() != Block::WATER)
        {
            Block newBlock = Block(Block::AIR, false, true, false);
            world.setBlock(x, y, z, newBlock);
            world.addCordsToUpdate(x, z);
            break;
        }
    }
}

glm::vec3 getPlacedBlockPosition(GLfloat x, GLfloat y, GLfloat z);

void Player::placeBlock(World &world, Camera &camera)
{
    glm::vec3 front = camera.getFront();
    glm::vec3 rayStep = {front.x * 0.05, front.y * 0.05, front.z * 0.05};
    for(auto rayPos = glm::vec3(0); glm::length(rayPos) < 4; rayPos += rayStep)
    {
        int x = floor(position.x + rayPos.x);
        int y = floor(position.y + .5 + rayPos.y);
        int z = floor(position.z + rayPos.z);
        auto block = world.getBlock(x, y, z);

        if(block.GetType() != Block::AIR && block.GetType() != Block::WATER)
        {
            glm::vec3 positionCorrection = getPlacedBlockPosition(position.x + rayPos.x, position.y + .5 + rayPos.y, position.z + rayPos.z);
            glm::vec3 newBlockPosition=  {x + positionCorrection.x, y + positionCorrection.y, z + positionCorrection.z};
            if(!isCollidingWithPlayer(newBlockPosition))
            {
                Block newBlock = Block(Block::GRASS, true, false, true);
                world.setBlock(newBlockPosition.x, newBlockPosition.y, newBlockPosition.z, newBlock);
                world.addCordsToUpdate(newBlockPosition.x, newBlockPosition.z);
            }
            break;
        }
    }
}

bool Player::isCollidingWithPlayer(const glm::vec3 &blockPosition) {
    glm::vec3 playerMinCorner = position - box.dimensions;
    glm::vec3 playerMaxCorner = position + glm::vec3{box.dimensions.x, 0.5, box.dimensions.z};

    glm::vec3 blockMinCorner = blockPosition;
    glm::vec3 blockMaxCorner = blockPosition + glm::vec3{1,1,1};

    bool xOverlap = playerMinCorner.x < blockMaxCorner.x && playerMaxCorner.x > blockMinCorner.x;
    bool yOverlap = playerMinCorner.y < blockMaxCorner.y && playerMaxCorner.y > blockMinCorner.y;
    bool zOverlap = playerMinCorner.z < blockMaxCorner.z && playerMaxCorner.z > blockMinCorner.z;

    return xOverlap && yOverlap && zOverlap;
}


glm::vec3 getPlacedBlockPosition(GLfloat x, GLfloat y, GLfloat z)
{
    double intpart;
    x = std::modf(x, &intpart);
    y = std::modf(y, &intpart);
    z = std::modf(z, &intpart);

    if(x < 0) x++;
    if(z < 0) z++;

    int vectors[6][3] = {
            {-1, 0, 0}, // Left face
            {1, 0, 0}, // Right face
            {0, -1, 0}, // Bottom face
            {0, 1, 0}, // Top face
            {0, 0, -1}, // Back face
            {0, 0, 1}  // Front face
    };

    std::pair leftFace = std::make_pair(x, 0);
    std::pair rightFace = std::make_pair(1 - x, 1);
    std::pair bottomFace = std::make_pair(y, 2);
    std::pair topFace = std::make_pair(1 - y, 3);
    std::pair backFace = std::make_pair(z, 4);
    std::pair frontFace = std::make_pair(1 - z, 5);

    std::vector<std::pair<GLfloat, int>> faces = {leftFace, rightFace, bottomFace, topFace, backFace, frontFace};

    auto minFace = std::min_element(faces.begin(), faces.end(),
                                    [](const std::pair<GLfloat, int>& a, const std::pair<GLfloat, int>& b) {
                                        return a.first < b.first;
                                    });

    int minFaceIndex = minFace->second;

    return {vectors[minFaceIndex][0], vectors[minFaceIndex][1], vectors[minFaceIndex][2]};
}