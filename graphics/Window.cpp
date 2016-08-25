#include "Window.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

#include <string>
#include <stdexcept>

namespace rekwarfare {

const Uint32 WINDOWPOS_UNDEF = SDL_WINDOWPOS_UNDEFINED;

Window::Window(std::string title, int x, int y, int width, int height,
    bool res, bool fullscreen)
    : m_title(title), m_x(x), m_y(y), m_width(width), m_height(height),
    m_resizable(res), m_fullscreen(fullscreen) {
    m_successsetup = setupWindow();
}

Window::~Window() {
    SDL_DestroyWindow(m_win);
}

SDL_Window* Window::operator()() {
    return m_win;
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
}

void Window::setHeight(unsigned int h) {
    SDL_SetWindowSize(m_win, m_width, h);
}

void Window::setVsyncEnabled(bool flag) {
    if (SDL_GL_SetSwapInterval((flag) ? 1 : 0) < 0) {
        SDL_Log("Vsync could not be enabled! (%s)", SDL_GetError());
    }
}

bool Window::setupWindow() {
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

int Window::getDrawWidth() const {
	int w;
	SDL_GL_GetDrawableSize(m_win, &w, nullptr);
	return w;
}

int Window::getDrawHeight() const {
	int h;
	SDL_GL_GetDrawableSize(m_win, nullptr, &h);
	return h;
}

}
