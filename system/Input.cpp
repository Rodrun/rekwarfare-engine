#include "Input.hpp"

namespace rekwarfare {

const MouseButton MOUSE_LEFT = SDL_BUTTON_LEFT;
const MouseButton MOUSE_MIDDLE = SDL_BUTTON_MIDDLE;
const MouseButton MOUSE_RIGHT = SDL_BUTTON_RIGHT;
const MouseButton MOUSE_X1 = SDL_BUTTON_X1;
const MouseButton MOUSE_X2 = SDL_BUTTON_X2;
const MouseButton MOUSE_LEFTMASK = SDL_BUTTON_LMASK;
const MouseButton MOUSE_MIDMASK = SDL_BUTTON_MMASK;
const MouseButton MOUSE_RIGHTMASK = SDL_BUTTON_RMASK;
const MouseButton MOUSE_X1MASK = SDL_BUTTON_X1MASK;
const MouseButton MOUSE_X2MASK = SDL_BUTTON_X2MASK;

namespace {
    SDL_Event* e = nullptr;
}

void setEvent(SDL_Event* ev) {
    e = ev;
}

int getJoystickCount() {
    return 0;
}

const char* getJoystickName(int index) {
    return "";
}

bool keyWasPressed() {
    return (e->type == SDL_KEYDOWN);
}

bool keyPressed(Key k) {
	const auto keypressed = getKey();
	return keypressed[k];
}

Key* getKey() {
    return (Key*) SDL_GetKeyboardState(nullptr);
}

bool mouseButtonPressed() {
    return (e->type == SDL_MOUSEBUTTONDOWN);
}

bool mouseButtonUp() {
    return (e->type == SDL_MOUSEBUTTONUP);
}

MouseButton getMouseButton() {
    return e->button.button;
}

bool mouseIsMoving() {
    return (e->type == SDL_MOUSEMOTION);
}

Sint32 getMouseX() {
    int x;
    SDL_GetMouseState(&x, nullptr);
    return x;
}

Sint32 getMouseY() {
    int y;
    SDL_GetMouseState(nullptr, &y);
    return y;
}

MouseButtonEvent getMouseButtonEvent() {
    return e->button;
}

MouseMotionEvent getMouseMotionEvent() {
    return e->motion;
}

}
