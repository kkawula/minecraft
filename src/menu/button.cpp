#include <iostream>
#include "Button.h"
#include <GLFW/glfw3.h>

Button::Button(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Button::render() const  {
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 1.0f);

    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);

    glEnd();
}

bool Button::isClicked(double xpos, double ypos) const {
    std::cout << "Button clicked at: " << xpos << ", " << ypos << std::endl;
    std::cout << "Button position: " << x << ", " << y << std::endl;
    std::cout << "Button size: " << width << ", " << height << std::endl;
    return xpos >= x && xpos <= x + width && ypos >= y && ypos <= y + height;
}