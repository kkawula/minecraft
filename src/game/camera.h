#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera();

    void processKeyboard(int key);

    glm::vec3 getPosition();

private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
};

#endif // CAMERA_H