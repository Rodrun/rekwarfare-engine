#pragma once
/*
* Window will handle the initialization of video-related SDL systems & OpenGL,
*  and of course, the drawing window.
*
* MACRO NOTES:
* Define REKWARFARE_GL_MAJOR and REKWARFARE_GL_MINOR if a different
*  OpenGL major and minor version is desired other than the default 2.1.
* Define REKWARFARE_IMG_INIT_FLAGS to your desired IMG_Init() flags, Default is
*  IMG_INIT_PNG.
* Define REKWARFARE_DONT_USE_IMAGE if SDL_Image is not desired.
* Define REKWARFARE_DONT_USE_TTF if SDL_TTF is not desired.
*
* NOTES:
* The window, if not fullscreen, by default is not resizable, use
*  setResizable().
*/
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include <string>

// 2.1 for compatability for most systems
#ifndef REKWARFARE_GL_MAJOR
#   define REKWARFARE_GL_MAJOR 2
#endif
#ifndef REKWARFARE_GL_MINOR
#   define REKWARFARE_GL_MINOR 1
#endif

#ifndef REKWARFARE_IMG_INIT_FLAGS
#   define REKWARFARE_IMG_INIT_FLAGS IMG_INIT_PNG
#endif

#define REKWARFARE_WINDOWPOS_UNDEF SDL_WINDOWPOS_UNDEFINED

namespace rekwarfare {

class Window {
public:
    Window(std::string title, int x, int y, int width, int height,
        bool resizable=false, bool fullscreen=false);
    ~Window();
    void pollEvents();
    /*
    * Swaps the OpenGL window.
    */
    void update();
    void clear(GLbitfield flags=GL_COLOR_BUFFER_BIT);
    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setVsyncEnabled(bool);
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getDrawableWidth() const { return m_draww; }
    int getDrawableHeight() const { return m_drawh; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    bool isRunning() const { return m_running; }
    bool vsyncEnabled() const { return m_vsync; }
    bool isResizable() const { return m_resizable; }
    bool isResized() const { return m_isResized; }
    bool isFocused() const { return m_focused; }
    bool hasMouseEntered() const { return m_mouseenter; }
    bool isFullscreen() const { return m_fullscreen; }
    std::string getTitle() const { return m_title; }
    SDL_Window* getWindow() const { return m_win; }
    SDL_Event e; // wontfix name

private:
    /*
    * Setup SDL, SDL_Window, OpenGL, and throw on error
    */
    void setupSystems();
    /*
    * setupX()
    * returns: true if no errors occured.
    */
    bool setupSDL();
    bool setupWindow();
    bool setupGL();
    void updateDrawDimensions();

    std::string m_title;
    int m_x = 0, m_y = 0, m_width = 0, m_height = 0, m_draww = 0, m_drawh = 0;
    bool m_vsync = true;
    bool m_running = true;
    bool m_resizable = false;
    // Window events
    bool m_isResized = false;
    bool m_minimized = false;
    bool m_maxmized = false;
    bool m_focused = false;
    bool m_mouseenter = false;
//    bool m_moved = false;
    bool m_fullscreen;
    SDL_Window* m_win = nullptr;
    SDL_GLContext m_glcontext;
};

}
