#include "window/window.h"

int main() {
    Window window(800, 600, "minecraft");

    while (!window.shouldClose()) {


        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
