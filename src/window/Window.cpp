#include <iostream>
#include "Window.h"
Window::Window(int width, int height, const char* title) : menu(this), game(this) {
    if (!glfwInit()) {
        return;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    this->currentState = &menu;

    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentState->update();
        currentState->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* windowObj = static_cast<Window*>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (windowObj) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            windowObj->menu.handleMouseClick(xpos, ypos);
    }
}

void Window::changeToMenu() {
    currentState = &menu;
    std::cout << "Changed to menu" << std::endl;
}

void Window::changeToGame() {
    currentState = &game;
    std::cout << "Changed to game" << std::endl;
}

int Window::getWidth() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::getHeight() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

GLFWwindow *Window::getWindow() {
    return window;
}
