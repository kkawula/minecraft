#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
Camera::Camera()  {}

void Camera::processKeyboard(int key) {
    std::cout << "key pressed " << key << std::endl;
    float cameraSpeed = 0.1f;
    if (key == GLFW_KEY_W)
        position.z -= cameraSpeed;
    if (key == GLFW_KEY_S)
        position.z += cameraSpeed;
    if (key == GLFW_KEY_A)
        position.x -= cameraSpeed;
    if (key == GLFW_KEY_D)
        position.x += cameraSpeed;
    if (key == GLFW_KEY_SPACE)
        position.y += cameraSpeed;
    if (key == GLFW_KEY_LEFT_CONTROL)
        position.y -= cameraSpeed;
}

glm::vec3 Camera::getPosition() {
    return position;
}
