#include "Window.hpp"

#include "SDL2/SDL.h"
#include "SDL_opengl.h"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <stdexcept>

namespace rekwarfare {

const Uint32 WINDOWPOS_UNDEF = SDL_WINDOWPOS_UNDEFINED;

Window::Window(std::string title, int x, int y, int width, int height,
    bool res, bool fullscreen)
    : m_title(title), m_x(x), m_y(y), m_width(width), m_height(height),
    m_resizable(res), m_fullscreen(fullscreen) {
    setupSystems();
    updateDrawDimensions();
}

Window::~Window() {
    SDL_DestroyWindow(m_win);

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
}

void Window::pollWindowEvents() {
    switch (e.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_WINDOWEVENT:
            switch (e.window.event) {
                case SDL_WINDOWEVENT_MINIMIZED:
                    m_minimized = true;
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    m_minimized = false;
                    m_maxmized = true;
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    m_minimized = false;
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    m_focused = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    m_focused = false;
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    m_mouseenter = true;
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    m_mouseenter = false;
                    break;
            }
            break;
    }
}

void Window::update() {
    SDL_GL_SwapWindow(m_win);
}

int Window::getEventPollingState() {
    return SDL_PollEvent(&e);
}

void Window::clear(GLbitfield flags) {
    glClear(flags);
}

void Window::setWidth(unsigned int w) {
    SDL_SetWindowSize(m_win, w, m_height);
    updateDrawDimensions();
}

void Window::setHeight(unsigned int h) {
    SDL_SetWindowSize(m_win, m_width, h);
    updateDrawDimensions();
}

void Window::setVsyncEnabled(bool flag) {
    if (SDL_GL_SetSwapInterval((flag) ? 1 : 0) < 0) {
        SDL_Log("Vsync could not be enabled! (%s)", SDL_GetError());
    }
}

void Window::setupSystems() {
    // keep in order!
    if (!setupSDL() || !setupWindow() || !setupGL())
        throw std::runtime_error("Failed to setup systems!");
}

bool Window::setupSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't init SDL! Reason: %s", SDL_GetError());
        return false;
    }
    if ((IMG_Init(REKWARFARE_IMG_INIT_FLAGS) & REKWARFARE_IMG_INIT_FLAGS)
        != REKWARFARE_IMG_INIT_FLAGS) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Could not init SDL_image! Reason: {}", IMG_GetError());
        return false;
    }
    if (TTF_Init() == -1) {
        SDL_Log("Could not init SDL_TTF! Reason: {}", TTF_GetError());
    }
    return true;
}

bool Window::setupWindow() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, REKWARFARE_GL_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, REKWARFARE_GL_MINOR);

    Uint32 flags =
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_SHOWN
        | SDL_WINDOW_ALLOW_HIGHDPI;
    if (m_resizable)
        flags = flags | SDL_WINDOW_RESIZABLE;
    m_win = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_width, m_height,
        flags);
    if (m_fullscreen) {
        int e = SDL_SetWindowFullscreen(m_win, 1);
        if (e < 0) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                "Could not set to fullscreen! Reason: %s", SDL_GetError());
        }
    }

    if (!m_win) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
            "Window failed to create!: %s", SDL_GetError());
        return false;
    }

    SDL_GetWindowPosition(m_win, &m_x, &m_y);
    return true;
}

bool Window::setupGL() {
    m_glcontext = SDL_GL_CreateContext(m_win);
    if (m_glcontext == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER,
            "OpenGL context failed to create! Reason: %s", SDL_GetError());
        return false;
    }

    SDL_GL_GetDrawableSize(m_win, &m_draww, &m_drawh);

    setVsyncEnabled(m_vsync);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, m_draww, m_drawh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0, m_width, m_height, 0, 1, -1);

    glClearColor(0, 0, 0, 1);
    return true;
}

void Window::updateDrawDimensions() {
    SDL_GL_GetDrawableSize(m_win, &m_draww, &m_drawh);
}

}
