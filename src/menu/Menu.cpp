#include <iostream>
#include "Menu.h"
#include "../window/window.h"

Menu::Menu(Window* window) : window(window), startButton(100, 100, 100, 50) {
    std::cout << "menu created" << std::endl;
}

void Menu::update() {
    double mouseX, mouseY;
    glfwGetCursorPos(window->getGLFWwindow(), &mouseX, &mouseY);

//    if (startButton.isClicked(mouseX, mouseY)) {
//        std::cout << "Button clicked" << std::endl;
//    }
//    std::cout <<mouseX << " " << mouseY << std::endl;
}

void Menu::handleMouseClick(double xpos, double ypos) {
    // Sprawdzamy, czy kliknięcie myszy nastąpiło w obszarze menu
    // W tym przykładzie zakładamy, że obszar menu znajduje się na całej wysokości okna
    // Możesz dostosować to do swoich potrzeb

    // Pobieramy wysokość okna
    int windowHeight;
    glfwGetWindowSize(window->getGLFWwindow(), nullptr, &windowHeight);


    std::cout << "Mouse clicked in menu at position: " << xpos << ", " << ypos << std::endl;

}

void Menu::render() {
    startButton.render();

    // Renderuj inne elementy menu
}

bool Menu::isActive() const {
    return active;
}
