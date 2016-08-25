#include <iostream>
#include <string>

#include "Rekwarfare.hpp"

using namespace rekwarfare;

bool ask(std::string);

int main(int argc, char* argv[]) {
	initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
	Window window("t3", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, 400, 400);
	initializeOpenGL(2, 1, window());

	std::string src, ans;
	Texture texture;
	FilterType min, mag;

	std::cout << "Enter image source:\n";
	std::cin >> src;
	min = ask("LINEAR min filter?") ? LINEAR : NEAREST;
	mag = ask("LINEAR mag filter?") ? LINEAR : NEAREST;
	if (!loadTexture(texture, src, min, mag)) {
		std::cout << "Failed to load texture\n";
		return 1;
	}

	while (window.isRunning()) {
		while (window.getEventPollingState() != 0) {
			window.pollWindowEvents();
		}
		window.clear();
		drawTexture(texture, 0, 0, window.getDrawWidth(),
			window.getDrawHeight(), 0, NO_COLOR);
		window.update();
	}
	deleteTexture(texture);
	destroySDL();
	return 0;
}

bool ask(std::string question) {
	std::cout << question << "\n";
	std::string answer;
	std::cin >> answer;
	if (answer.compare("yes") == 0)
		return true;
	return false;
}
