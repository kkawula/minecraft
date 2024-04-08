#include <iostream>
#include "menu.h"
#include "../window/Window.h"

Menu::Menu(Window* window) : window(window), startButton(-0.25f, -0.25f, 0.5f, 0.5f) {
    std::cout << "menu created" << std::endl;
}


void Menu::handleMouseClick(double xpos, double ypos) {

    // normalized to [-1, 1]
    double normalizedX = 2 * (xpos - window->getWidth()/2.0) / window->getWidth();
    double normalizedY = 2 * (ypos - window->getHeight()/2.0) / window->getHeight();

    if (startButton.isClicked(normalizedX, normalizedY)) {
        std::cout << "Start button was clicked." << std::endl;
        std::cout << "Game started." << std::endl;
        window->changeToGame();
    } else {
        std::cout << "Mouse clicked in menu at position: " << normalizedX << ", " << normalizedY << std::endl;
    }
}

void Menu::update() {
}

void Menu::render() {
    startButton.render();
}