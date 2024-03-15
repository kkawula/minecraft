#include "config.h"
#include "window/Window.h"

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    window.run();

    return 0;
}
