#include <iostream>
#include "window.h"

Window::Window(int width, int height, const char* title) : menu(this) {
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

GLFWwindow* Window::getGLFWwindow() {
    return window;
}

Menu& Window::getMenu() {
    return menu;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* windowObj = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (windowObj) {
        // Wywołanie metody mouse_button_callback na obiekcie Window
        windowObj->menu.handleMouseClick(10, 10);
    }
}