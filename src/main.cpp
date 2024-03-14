#include "config.h"
#include "window/window.h"

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    while (!window.shouldClose()) {


        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
