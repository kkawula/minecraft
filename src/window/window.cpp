#include <iostream>
#include "window.h"

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    std::cout << "Window created" << std::endl;
    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}
