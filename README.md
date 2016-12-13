# Rekwarfare engine (really a framework)

(I like to call it the RW Engine)

A 2D game framework that utilizes SDL2 and OpenGL.

## What is it for?

Ideally, any 2D game that doesn't need best-of-the-industry-features-and-tech.

## What are its features?

Not much, I'm developing this to be very generic and "barebones"-ish. It can
do the following:

* Handle SDL Windows
* Render textures
* Play audio
* Run a server (to be rewritten soon!)

# Dependencies

[OpenGL](https://opengl.org/)

[SDL2](http://libsdl.org/)

[SDL2_image](http://www.libsdl.org/projects/SDL_image/)

[SDL2_ttf](http://www.libsdl.org/projects/SDL_ttf/)

[SDL2_mixer](http://www.libsdl.org/projects/SDL_mixer/)

# Building

Building is pretty simple, feel free to modify the CMakeLists.txt to fit your needs.

## Windows

Clone the repository, make a separate directory to have build files, then build from that directory.

Requires [CMake](https://cmake.org/) and a C++ compiler like [MinGW](http://www.mingw.org/).

So you should do something like this:

1- Clone/download the source

2- Create a separate directory to have build files

3- Open command prompt and navigate to that directory

4- `cmake <source directory> -G "MinGW Makfiles"`

5- `mingw32-make`

## Linux

Pretty simple, just clone repository, have a separate directory to have build files, then build from that directory.

Requires [CMake](https://cmake.org/) (and git if you don't already have it)!

So following the instructions, you should do something like this:

```sh
git clone https://github.com/rodrun/rekwarfare-engine.git
mkdir build
cd build
cmake <wherever rekwarfare-engine repository is>
make
```

# Starting off

I try my best to make the engine very simple to use. To get a window started up and running you can do the following:

```cpp
using namespace rw;
// Feel free to change any of these parameters
initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
Window window("A window!", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, 800, 400);
initializeOpenGL(2, 1, window());
while (window.isRunning()) {
    while (window.getEventPollingState() != 0) {
        window.pollWindowEvents();
        switch (window.e) {
            // Check for some events
        }
    }
    window.clear();
    // Do some stuff here
    window.update();
}
destroySDL();
```

**Remember** that everything is within the namespace 'rekwarfare' or 'rw'.

Please see the documentation for more. (to be written soon!)
