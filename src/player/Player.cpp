#include "Player.h"
#include "GLFW/glfw3.h"

Player::Player(const glm::vec3 &pos)
        : Entity({pos}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
        , acceleration(glm::vec3(0.f))
{
}

void Player::handleInput(Keyboard keyboard, Camera &camera, World &world, GLfloat deltaTime) {
    GLfloat speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 2.0f : 1.0f;
    GLfloat velocity = this->movementSpeed * deltaTime * speedMultiplier;

    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();
    glm::vec3 worldUp = camera.getWorldUp();

    glm::vec3 move = glm::vec3(0.0f);

    if (keyboard.isKeyDown(GLFW_KEY_W))
        move += front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_S))
        move -= front * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_A))
        move -= right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_D))
        move += right * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_SPACE))
        move += worldUp * velocity;

    if (keyboard.isKeyDown(GLFW_KEY_LEFT_CONTROL))
        move -= worldUp * velocity;

    glm::vec3 newPosition = this->position + move;
    auto [collision, collisionNormal] = CheckCollision(world, newPosition);

    if (collision) {
        // Adjust the movement vector along the collision normal direction
        move = glm::reflect(move, collisionNormal); // Reflect the movement vector along the collision normal
        newPosition = this->position + move;

        // Check if the player is still colliding with other blocks
        std::tie(collision, collisionNormal) = CheckCollision(world, newPosition);
        if (collision) {
            // Stop movement if still colliding
            newPosition = this->position;
        }
    }

    this->position = newPosition;
    camera.setPosition(this->position); // Aktualizacja pozycji kamery na pozycji gracza
}

void Player::handleMouseMovement(Camera &camera, GLfloat xOffset, GLfloat yOffset)
{
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void Player::handleMouseScroll(Camera &camera, GLfloat yOffset)
{
    camera.ProcessMouseScroll(yOffset);
}

std::tuple<bool, glm::vec3> Player::CheckCollision(World &world, glm::vec3 newPosition) {
    // Player dimensions
    float width = 0.3f;
    float height = 2.0f;
    float depth = 0.3f;

    // Player vertices
    glm::vec3 vertices[8] = {
            newPosition + glm::vec3(-width, -height, -depth), // Front-left-bottom
            newPosition + glm::vec3(-width, -height, depth),  // Front-left-top
            newPosition + glm::vec3(-width, height, -depth),  // Front-right-bottom
            newPosition + glm::vec3(-width, height, depth),   // Front-right-top
            newPosition + glm::vec3(width, -height, -depth),  // Back-left-bottom
            newPosition + glm::vec3(width, -height, depth),   // Back-left-top
            newPosition + glm::vec3(width, height, -depth),   // Back-right-bottom
            newPosition + glm::vec3(width, height, depth)     // Back-right-top
    };

    // Player edges
    glm::vec3 edges[12] = {
            vertices[0] - vertices[1], // Front-left
            vertices[0] - vertices[2], // Front-bottom
            vertices[0] - vertices[4], // Left-bottom
            vertices[1] - vertices[3], // Front-top
            vertices[1] - vertices[5], // Left-top
            vertices[2] - vertices[3], // Bottom-right
            vertices[2] - vertices[6], // Front-right
            vertices[3] - vertices[7], // Right-top
            vertices[4] - vertices[5], // Back-left
            vertices[4] - vertices[6], // Back-bottom
            vertices[5] - vertices[7], // Left-back
            vertices[6] - vertices[7]  // Right-back
    };

    bool collision = false;
    glm::vec3 collisionNormal = glm::vec3(0.0f);

    // Check collision at each vertex and edge of the player
    for (int i = 0; i < 8; ++i) {
        glm::vec3 vertex = vertices[i];
        if (world.getBlock(vertex.x, vertex.y, vertex.z).IsSolid()) {
            // Calculate collision normal as the vector from the vertex to the new player position
            collisionNormal += newPosition - vertex;
            collision = true;
        }
    }

    // Check collision along each edge of the player
    for (int i = 0; i < 12; ++i) {
        glm::vec3 edge = edges[i];
        glm::vec3 edgeCenter = (vertices[i / 2] + vertices[i / 2 + 1]) * 0.5f; // Center of the edge
        if (world.getBlock(edgeCenter.x, edgeCenter.y, edgeCenter.z).IsSolid()) {
            // Calculate collision normal as the vector from the edge center to the new player position
            collisionNormal += newPosition - edgeCenter;
            collision = true;
        }
    }

    // Check collision along each face of the player
    glm::vec3 faceCenters[6] = {
            (vertices[0] + vertices[1] + vertices[2] + vertices[3]) * 0.25f, // Front face center
            (vertices[4] + vertices[5] + vertices[6] + vertices[7]) * 0.25f, // Back face center
            (vertices[0] + vertices[1] + vertices[4] + vertices[5]) * 0.25f, // Left face center
            (vertices[2] + vertices[3] + vertices[6] + vertices[7]) * 0.25f, // Right face center
            (vertices[1] + vertices[3] + vertices[5] + vertices[7]) * 0.25f, // Top face center
            (vertices[0] + vertices[2] + vertices[4] + vertices[6]) * 0.25f  // Bottom face center
    };

    for (int i = 0; i < 6; ++i) {
        glm::vec3 faceCenter = faceCenters[i];
        if (world.getBlock(faceCenter.x, faceCenter.y, faceCenter.z).IsSolid()) {
            // Calculate collision normal as the vector from the face center to the new player position
            collisionNormal += newPosition - faceCenter;
            collision = true;
        }
    }

    if (collision) {
        collisionNormal = glm::normalize(collisionNormal);
    }

    return std::make_tuple(collision, collisionNormal);
}

glm::vec3 Player::ResolveCollision(glm::vec3 desiredMove, glm::vec3 collisionNormal) {
    // Przesuń gracza w kierunku przeciwnym do normalnej kolizji
    return desiredMove - glm::dot(desiredMove, collisionNormal) * collisionNormal;
}