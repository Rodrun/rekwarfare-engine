/*
* Collection of functions and datatypes to initialize and deinitialize
*  SDL & OpenGL.
*/
#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace rekwarfare {

typedef SDL_GLContext GLContext;
typedef Uint32 SetupFlags;
typedef int ImageFlags;
typedef int AudioFlags;

// Some wraps
const extern SetupFlags INIT_EVERYTHING;
const extern SetupFlags INIT_TIMER;
const extern SetupFlags INIT_AUDIO;
const extern SetupFlags INIT_VIDEO;
const extern SetupFlags INIT_JOYSTICK;
const extern SetupFlags INIT_HAPTIC;
const extern SetupFlags INIT_GAMECONTROLLER;
const extern ImageFlags IMG_JPG;
const extern ImageFlags IMG_PNG;
const extern ImageFlags IMG_TIF;
const extern ImageFlags IMG_WEBP;
const extern AudioFlags MIX_FLAC;
const extern AudioFlags MIX_MOD;
const extern AudioFlags MIX_MP3;
const extern AudioFlags MIX_OGG;

/*
* Initialize SDL.
* f: Flags for SDL initialization.
* i: Flags for SDL_Image initialization. (Can be OR'd with other ImageFlags)
* a: Flags for SDL_Mixer initialization. (Can be OR'd with other AudioFlags)
* returns: True on success, false on failure.
*/
bool initializeSDL(SetupFlags f, ImageFlags i, AudioFlags a);
/*
* Initialize an OpenGL context.
* major: OpenGL Major version.
* minor: OpenGL Minor version.
* win: The window which to create the context in.
* returns: NULL on failure.
*/
GLContext initializeOpenGL(int major, int minor, SDL_Window* win);
/*
* Destroy SDL.
*/
void destroySDL();

}
