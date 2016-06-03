# Rekwarfare engine

(I like to call it the RW Engine)

A 2D game engine that utilizes SDL2 and OpenGL.

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

I currently only know how to build on GNU/Linux systems...

## Linux

Pretty simple, just clone repository, have a separate directory to have build files, then build from that directory.

So following the instructions, you should do something like this:

```
$ git clone https://github.com/rodrun/rekwarfare-engine.git
$ mkdir build
$ cd build
$ cmake <wherever rekwarfare-engine repository is>
$ make
```

# Starting off

I try my best to make the engine very simple to use. To get a window started up and running you can do the following:

```
using namespace rekwarfare;
// Feel free to change any of these parameters
initializeSDL(INIT_EVERYTHING, IMG_PNG, MIX_MP3);
Window window("A window!", WINDOWPOS_UNDEF, WINDOWPOS_UNDEF, 800, 400);
initializeOpenGL(window());
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
```

**Remember** that everything is within the namespace 'rekwarfare'.

Please see the documentation for more. (to be written soon!)
