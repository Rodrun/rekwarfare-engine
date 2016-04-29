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

    while (window.isRunning()) {
        window.pollEvents();
        window.clear();

        drawTexture(t, 0, 0, window.getWidth(), window.getHeight(), 0, NO_COLOR);

        window.update();
    }
    return 0;
}
