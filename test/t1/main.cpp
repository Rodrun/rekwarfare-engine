#include <iostream>
#include "Rekwarfare.hpp"

using namespace rekwarfare;

int main() {
    initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
    Window window("t1", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, 800, 640);
    initializeOpenGL(2, 1, window());

    Texture t;
    bool loaded = loadTexture(t, "test/resource/t1.png");
    if (!loaded) {
        std::cout << "t1.png couldn't be loaded!" << std::endl;
        return 1;
    }

    Font* f = loadFont("test/resource/AIRSTREA.TTF", 24);
    if (f == nullptr) {
        std::cout << "AIRSTREA.TTF couldn't be loaded!" << std::endl;
        return 1;
    }

    float rotation = 0;
    Color c = { 1, 0, 0, 1 };
    Color bg = { 0, 1, 0, 1 };

    while (window.isRunning()) {
        while (window.getEventPollingState() != 0) {
            window.pollWindowEvents();
        }

        if (rotation >= 360)
            rotation = 0;
        else
            rotation++;

        window.clear();

        drawRectangle(0, 0, 250, 250, rotation, c);
        drawRectangle(400, 150, 100, 200, -rotation, bg);
        drawLine(125, 125, 425, 150, 0, bg);
        drawTexture(t, 0, 0, window.getWidth(), window.getHeight(), 0, NO_COLOR);
        drawText("RW Engine", f, 0, window.getHeight() - 200, 800 / 3, 200,
            0, c, BLENDED);
        drawText_shaded("t1", f, 0, window.getHeight() - 256, 800 / 16, 200, 0,
            c, bg);

        window.update();
    }

    deleteTexture(t);
    deleteFont(f);
    return 0;
}
