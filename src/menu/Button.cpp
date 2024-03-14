#include "Button.h"
#include <GLFW/glfw3.h>

Button::Button(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool Button::isClicked(int mouseX, int mouseY) const {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

void Button::render() const {
    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f); // Biały

    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);

    glEnd();
}