#include "System.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_opengl.h"

namespace rekwarfare {

const SetupFlags INIT_EVERYTHING = SDL_INIT_EVERYTHING;
const SetupFlags INIT_TIMER = SDL_INIT_TIMER;
const SetupFlags INIT_AUDIO = SDL_INIT_AUDIO;
const SetupFlags INIT_VIDEO = SDL_INIT_VIDEO;
const SetupFlags INIT_JOYSTICK = SDL_INIT_JOYSTICK;
const SetupFlags INIT_HAPTIC = SDL_INIT_HAPTIC;
const SetupFlags INIT_GAMECONTROLLER = SDL_INIT_GAMECONTROLLER;
const ImageFlags IMG_JPG = IMG_INIT_JPG;
const ImageFlags IMG_PNG = IMG_INIT_PNG;
const ImageFlags IMG_TIF = IMG_INIT_TIF;
const ImageFlags IMG_WEBP = IMG_INIT_WEBP;
const AudioFlags MIX_FLAC = MIX_INIT_FLAC;
const AudioFlags MIX_MOD = MIX_INIT_MOD;
const AudioFlags MIX_MP3 = MIX_INIT_MP3;
const AudioFlags MIX_OGG = MIX_INIT_OGG;

const int DEFAULT_MINOR = 1;
const int DEFAULT_MAJOR = 2;

bool initializeSDL(SetupFlags f, ImageFlags i, AudioFlags a) {
    if (SDL_Init(f) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't init SDL! Reason: %s", SDL_GetError());
        return false;
    }
    if ((IMG_Init(i) & i) != i) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't init SDL_Image! Reason %s", IMG_GetError());
        return false;
    }
    if (TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Could not init SDL_TTF! Reason: %s", TTF_GetError());
        return false;
    }
    if ((Mix_Init(a) & a) != a) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Could not init SDL_Mixer! Reason: %s", Mix_GetError());
        return false;
    }
    return true;
}

GLContext initializeOpenGL(int major, int minor, SDL_Window* win) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

    SDL_GLContext ret = SDL_GL_CreateContext(win);
    if (ret == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "OpenGL context failed to create! Reason: %s", SDL_GetError());
        return ret;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0, w, h, 0, 1, -1);
    return ret;
}

void destroySDL() {
    while (Mix_Init(0))
        Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}
