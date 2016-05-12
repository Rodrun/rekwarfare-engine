#include <iostream>
#include "Rekwarfare.hpp"

using namespace rekwarfare;

int main() {
    Window window("t1", REKWARFARE_WINDOWPOS_UNDEF, REKWARFARE_WINDOWPOS_UNDEF,
        800, 640);

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

    Color c = { 1, 0, 0, 0 };
    Color bg = { .5, .5, .25, 1 };

    while (window.isRunning()) {
        window.pollEvents();
        window.clear();

        drawTexture(t, 0, 0, window.getWidth(), window.getHeight(), 0, NO_COLOR);
        drawText("RW Engine", f, 0, window.getHeight() - 200, 800 / 3, 200,
            0, c, BLENDED);
        //drawText_shaded("t1", f, 0, window.getHeight() - 256, 800 / 16, 200, 0,
        //    c, bg);

        window.update();
    }

    deleteTexture(t);
    deleteFont(f);
    return 0;
}
