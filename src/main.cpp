#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


void renderTriangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

void renderSquare() {

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
}

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
    #define GL_SILENCE_DEPRECATION
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "minecraft", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        renderSquare();
        renderTriangle();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
