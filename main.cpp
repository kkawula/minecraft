#include <iostream>
#include <glm/glm.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;
    glm::vec3 vector1(1.0f, 0.0f, 0.0f);
    glm::vec3 vector2(0.0f, 1.0f, 0.0f);
    glm::vec3 sum = vector1 + vector2;
    std::cout << "Sum: " << sum.x << ", " << sum.y << ", " << sum.z << std::endl;

    return 0;
}
