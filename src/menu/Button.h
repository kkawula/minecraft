#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button(int x, int y, int width, int height);
    bool isClicked(int mouseX, int mouseY) const;
    void render() const;

private:
    int x, y;
    int width, height;
};

#endif // BUTTON_H
