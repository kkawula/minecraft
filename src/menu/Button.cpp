#include "Button.h"
#include <GLFW/glfw3.h>

Button::Button(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    // It does not make sens
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Button::render()  {
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 1.0f);

    // this too
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);

    glEnd();
}

bool Button::isClicked(double xpos, double ypos) {
    return xpos >= x && xpos <= x + width && ypos >= y && ypos <= y + height;
}