# Rekwarfare engine

A 2D game engine that utilizes SDL2 and OpenGL.

## What is it for?

Ideally, any 2D game that doesn't need best-of-the-industry-features-and-tech.

## What are its features?

Not much, I'm developing this to be very generic and "barebones"-ish. It can
do the following:

* Handle SDL Windows
* Render textures
* Play audio
* Run a server

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
 $ git clone .../rekwarfare-engine.git
$ mkdir build
$ cd build
$ cmake <wherever rekwarfare-engine repository is>
$ make
```
