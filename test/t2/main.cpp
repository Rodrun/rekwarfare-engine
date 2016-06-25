#include <iostream>

#include "Rekwarfare.hpp"

#define WIDTH 800
#define HEIGHT 640

using namespace rekwarfare;

int main() {
    // Initialize with RW-engine
    initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
    Window window("t2", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, WIDTH, HEIGHT);
    initializeOpenGL(2, 1, window());
    setEvent(&window.e);

    //GUIEnvironment environment;
    Entity a(300, 300, 100, 100);
    Entity b(0, 0, 100, 100);
    while (window.isRunning()) {
        while (window.getEventPollingState() != 0) {
            window.pollWindowEvents();
        }

        b.x = getMouseX();
        b.y = getMouseY();

        window.clear();
        if (!a.collides(b))
            drawRectangle(a.x, a.y, a.w, a.h, 0, RED);
        else
            drawRectangle(a.x, a.y, a.w, a.h, 0, GREEN);
        drawRectangle(b.x, b.y, b.w, b.h, 0, BLUE);
        window.update();
    }

    destroySDL();
    return 0;
}
