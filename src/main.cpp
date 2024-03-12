#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


int main() {
    std::cout << "Hello, World!" << std::endl;
    glm::vec3 vector1(1.0f, 0.0f, 0.0f);
    glm::vec3 vector2(0.0f, 1.0f, 0.0f);
    glm::vec3 sum = vector1 + vector2;
    std::cout << "Sum: " << sum.x << ", " << sum.y << ", " << sum.z << std::endl;

    GLFWwindow* window;

    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
