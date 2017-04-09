/*
* Assists in handling input of all sorts supported by SDL.
*/
#pragma once

#include "SDL.h"

namespace rekwarfare {

typedef SDL_JoyAxisEvent JoyAxisEvent;
typedef SDL_JoyBallEvent JoyBallEvent;
typedef SDL_JoyHatEvent JoyHatEvent;
typedef SDL_JoyButtonEvent JoyButtonEvent;
typedef SDL_Joystick Joystick;
typedef Uint8 Key;
typedef Uint8 MouseButton;
typedef SDL_MouseButtonEvent MouseButtonEvent;
typedef SDL_MouseMotionEvent MouseMotionEvent;

const extern MouseButton MOUSE_LEFT;
const extern MouseButton MOUSE_MIDDLE;
const extern MouseButton MOUSE_RIGHT;
const extern MouseButton MOUSE_X1;
const extern MouseButton MOUSE_X2;
// Masks are used when checking with mouse motion events
const extern MouseButton MOUSE_LEFTMASK;
const extern MouseButton MOUSE_MIDMASK;
const extern MouseButton MOUSE_RIGHTMASK;
const extern MouseButton MOUSE_X1MASK;
const extern MouseButton MOUSE_X2MASK;

/*
* Set the  that the input handling will be using to get mouse events & data.
*/
void setEvent(SDL_Event*);
/*
* Get the amount of joysticks. Note that the last joystick is the count - 1.
* returns: The amount of joysticks.
*/
int getJoystickCount();
/*
* index: The N'th joystick on the system.
* returns: The name of a given joystick.
*/
const char* getJoystickName(int index);
/*
* Check if a key was pressed.
*/
bool keyWasPressed();
/*
* Check if a certain key or keys were pressed.
*/
bool keyPressed(Key);
/*
* Get key pressed.
*/
Key* getKey();
/*
* Check if a mouse button has been pressed.
*/
bool mouseButtonPressed();
/*
* Check if a mouse button is released.
*/
bool mouseButtonUp();
/*
* Get mouse button that was pressed.
*/
MouseButton getMouseButton();
/*
* Check if the mouse is in motion.
*/
bool mouseIsMoving();
/*
* Get the mouse X, relative to the window.
*/
Sint32 getMouseX();
/*
* Get the mouse Y, relative to the window.
*/
Sint32 getMouseY();
/*
* Get number of clicks from the mouse.
*/
int getClicks();
MouseButtonEvent getMouseButtonEvent();
MouseMotionEvent getMouseMotionEvent();

}
