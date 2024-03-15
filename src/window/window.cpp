#include <iostream>
#include "window.h"
Window::Window(int width, int height, const char* title) : menu(this), game(this) {
    if (!glfwInit()) {
        return;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::run() {


    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        if (menu.isActive()) {
            menu.update();
            menu.render();
        }else {
            std::cout << "Error: no active window" << std::endl;
        }
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