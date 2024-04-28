//
// Created by Kamil on 28/04/2024.
//

#include "Window.h"

#include <iostream>


Window::Window(unsigned int width, unsigned int height, const char* title)
        : width(width), height(height), title(title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}


void Window::setKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback) {
    glfwSetScrollCallback(window, callback);
}