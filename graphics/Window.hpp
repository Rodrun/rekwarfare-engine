/*
* The SDL Window that is used for rendering.
*/
#pragma once
#include "SDL.h"
#include "SDL_opengl.h"

#include <string>

namespace rekwarfare {

/*
* Undefined window position.
*/
const extern Uint32 WINDOWPOS_UNDEF;

class Window {
public:
    Window(std::string title, int x, int y, int width, int height,
        bool resizable=false, bool fullscreen=false);
    ~Window();
    SDL_Window* operator()();
    /*
    * Handle updating information on basic window states.
    * NOTE: This function already checks for the following:
    * SDL_WINDOWEVENT_MINIMIZED
    * SDL_WINDOWEVENT_MAXIMIZED
    * SDL_WINDOWEVENT_RESTORED
    * SDL_WINDOWEVENT_FOCUS_GAINED
    * SDL_WINDOWEVENT_FOCUS_LOST
    * SDL_WINDOWEVENT_ENTER
    * SDL_WINDOWEVENT_LEAVE
    */
    void pollWindowEvents();
    /*
    * Swaps (updates) the OpenGL window. Typically called after all rendering
    *  functions have been called.
    */
    void update();
    /*
    * Poll SDL's event and check if there is an event.
    * NOTE: Use hasEventsReady() for better semantics. Typically one would
    *  check if the return is not equal (!=) to 0.
    * returns: 0 when no state.
    */
    int getEventPollingState();
    /*
    * Check if there are any SDL Events to check.
    * returns: true if there are events to check, false otherwise.
    */
    bool hasEventsReady();
    /*
    * Clear the screen.
    */
    void clear(GLbitfield flags=GL_COLOR_BUFFER_BIT);
    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setVsyncEnabled(bool);
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    /*
    * Get the screen's drawable width.
    */
    int getDrawWidth() const;
    /*
    * Get the screen's drawable height.
    */
    int getDrawHeight() const;
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    bool isRunning() const { return m_running; }
    bool hasVsyncEnabled() const { return m_vsync; }
    bool isResizable() const { return m_resizable; }
    bool isFocused() const { return m_focused; }
    /*
    * Check if the mouse is inside the window.
    */
    bool hasMouseEntered() const { return m_mouseenter; }
    bool isFullscreen() const { return m_fullscreen; }
    /*
    * Check if the window setup successfully.
    */
    bool setupSuccessfully() const { return m_successsetup; }
    std::string getTitle() const { return m_title; }
    SDL_Window* getWindow() const { return m_win; }
    SDL_Event e; // wontfix name

private:
    bool setupWindow();

    std::string m_title;
    int m_x = 0, m_y = 0, m_width = 0, m_height = 0;
    SDL_Window* m_win = nullptr;
    /* Successful setup of window? */
    bool m_successsetup;
    bool m_vsync = true;
    bool m_running = true;
    bool m_resizable = false;
    // Window events
    bool m_minimized = false;
    bool m_maxmized = false;
    bool m_focused = false;
    bool m_mouseenter = false;
    bool m_fullscreen;
};

}
