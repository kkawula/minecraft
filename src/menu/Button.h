#ifndef BUTTON_H
#define BUTTON_H

#include <GLFW/glfw3.h>

class Button {
public:
    Button(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    void render();
    bool isClicked(double xpos, double ypos);

private:
    GLfloat x, y;
    GLfloat width, height;
};

#endif // BUTTON_H
