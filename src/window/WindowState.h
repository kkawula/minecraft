#ifndef WINDOWSTATE_H
#define WINDOWSTATE_H

class WindowState {
public:
    virtual void update() = 0;
    virtual void render() = 0;
};


#endif //WINDOWSTATE_H
