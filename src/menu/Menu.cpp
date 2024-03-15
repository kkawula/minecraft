#include <iostream>
#include "Menu.h"
#include "../window/window.h"

Menu::Menu(Window* window) : window(window), startButton(-0.25f, -0.25f, 0.5f, 0.5f) {
    std::cout << "menu created" << std::endl;
}

void Menu::update() {
}

void Menu::handleMouseClick(double xpos, double ypos) {

    double normalizedX = (xpos - window->getWidth()/2.0) / window->getWidth();
    double normalizedY = (window->getHeight()/2.0 - ypos) / window->getHeight();

    if (startButton.isClicked(normalizedX, normalizedY)) {
        std::cout << "Start button was clicked." << std::endl;
        std::cout << "Game started." << std::endl;
        window->setActiveGame();
    } else {
        std::cout << "Mouse clicked in menu at position: " << normalizedX << ", " << normalizedY << std::endl;
    }
}

void Menu::render() {
    startButton.render();
}

bool Menu::isActive() const {
    return active;
}
