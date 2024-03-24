#include <iostream>
#include "Game.h"
#include "../window/Window.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);

Game::Game(Window* window) {
    this->window = window;
    std::cout << "game created" << std::endl;
}

void Game::update() {
    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        cameraPosition.z -= 0.1f;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        cameraPosition.z += 0.1f;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        cameraPosition.x -= 0.1f;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        cameraPosition.x += 0.1f;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPosition.y += 0.1f;
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraPosition.y -= 0.1f;
    }
}

void Game::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int width = window->getWidth();
    int height = window->getHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glMultMatrixf(glm::value_ptr(view));

    glBegin(GL_QUADS);
    // Ściana przednia
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);   // top-left

    // Ściana tylna
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);   // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // top-left

    // Ściana górna
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);   // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);   // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // top-left

    // Ściana dolna
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // top-left

    // Ściana lewa
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);   // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // top-left

    // Ściana prawa
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // bottom-left
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   // bottom-right
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);    // top-right
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);   // top-left

    glEnd();
}