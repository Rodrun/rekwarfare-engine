# Rekwarfare engine (really more of a framework)

A 2D game framework that utilizes SDL2 and OpenGL.

(Not completely done yet!)

## What is it for?

Ideally, any 2D game that doesn't need best-of-the-industry-features-and-tech.

## What are its features?

Not much, I'm developing this to be very generic and "barebones"-ish. Also keep in mind that I've setup some things to fit __my__ needs as well.

But you can enjoy:

* SDL and OpenGL initialization (and SDL destruction, if you're worried)
* SDL Window handling
* Texture handling
* TTF Font handling
* Audio handling

## Wait, why is it "Not completely done yet"?

I wrote a lot of this code a while ago, and my needs and programming practices have changed.

So, because of that, I need to clean up some code and reorganize as well, but along with that I'm also adding more features and fixes.

# Dependencies

[SDL2](http://libsdl.org/)

[SDL2_image](http://www.libsdl.org/projects/SDL_image/)

[SDL2_ttf](http://www.libsdl.org/projects/SDL_ttf/)

[SDL2_mixer](http://www.libsdl.org/projects/SDL_mixer/)

(Your system should already have this)
[OpenGL](https://opengl.org/)

# Building

Building is pretty simple, feel free to modify the CMakeLists.txt to fit your needs.

## Windows

Clone the repository, make a separate directory to have build files, then build from that directory.

Requires [CMake](https://cmake.org/) and a C++ compiler such as [MinGW](http://www.mingw.org/).

So you should do something like this:

1- Clone/download the source

2- Create a separate directory to have build files

3- Open command prompt and navigate to that directory

4- `cmake <source directory> -G "MinGW Makefiles"`

5- `mingw32-make`

## Linux

Pretty simple, just clone repository, have a separate directory to have build files, then build from that directory.

Requires [CMake](https://cmake.org/) (and git if you don't already have it)!

So following the instructions, you should do something like this:

```sh
git clone https://github.com/rodrun/rekwarfare-engine.git
mkdir build
cd build
cmake <path to rekwarfare-engine repository>
make
```

# Starting off

I try my best to make the engine simple to use. To get a window started up and running you can do the following:

```cpp
#include "Rekwarfare.hpp"
int main(int argc, char* argv[]) {
    using namespace rw;
    // Feel free to change any of these parameters
    initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
    Window window("A window!", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, 800, 400);
    initializeOpenGL(2, 1, window());
    while (window.isRunning()) {
        while (window.getEventPollingState() != 0) {
            window.pollWindowEvents(); // Handle main window events
            switch (window.e) {
                // Check for some window events for yourself if you'd like
            }
        }
        window.clear();
        // Do some stuff here such as rendering
        window.update();
    }
    destroySDL();
}
```

**Remember** that everything is within the namespace 'rekwarfare' or 'rw'.

As of right now, documentation is in the source code, but I will be writing actual docs once I believe that this project is "finished enough."
