#pragma once

#include "Drawer.hpp"
#include "SDL.h"
#include "SDL_opengl.h"

#include <string>
#include <memory>

namespace rekwarfare {

/* Texture ID */
typedef GLuint Tid;

class Texture {
public:
    /*
    * Initialize an empty texture.
    */
    Texture() { }
    /*
    * Initialize from an SDL_Surface.
    */
    Texture(SDL_Surface*, FilterType min=getDefaultMinFilterType(),
        FilterType mag=getDefaultMagFilterType(),
        WrapMode wm=getWrappingMode());
    /*
    * Initialize a texture from given image path.
    * path - Relative location of image.
    */
    Texture(std::string path, FilterType min=getDefaultMinFilterType(),
        FilterType mag=getDefaultMagFilterType(),
        WrapMode wm=getWrappingMode());
    ~Texture();
    /*
    * Load a texture from given image path.
    * path - Relative location of image.
    * returns: True on success, false otherwise.
    */
    bool loadTexture(std::string path, FilterType min=getDefaultMinFilterType(),
        FilterType mag=getDefaultMagFilterType(),
        WrapMode wm=getWrappingMode());
    /*
    * Load a texture from an existing SDL_Surface.
    * returns: True on success, false otherwise.
    */
    bool loadTextureFromSurface(SDL_Surface* s,
        FilterType min=getDefaultMinFilterType(),
        FilterType mag=getDefaultMagFilterType(),
        WrapMode wm=getWrappingMode());
    /*
    * Draw a section of a texture.
    * tx/ty: Tile x/y
    * tw/th: Tile width/height
    */
    void render(double x, double y, double w, double h,
        unsigned int tx, unsigned int ty, unsigned int tw, unsigned int th,
        double rotation, Color=NO_COLOR, Flip=NOFLIP) const;
    /*
    * Render a whole image.
    */
    void render(double x, double y, double w, double h, double rotation,
        Color=NO_COLOR, Flip=NOFLIP) const;
    /*
    * Free the texture.
    */
    void free();
    int rawImageWidth() const { return mimg_width; }
    int rawImageHeight() const { return mimg_height; }

private:
    Tid mid;
    std::shared_ptr<SDL_Surface> msurface;
    int mimg_width, mimg_height;

    void loadTextureGL(SDL_Surface*, FilterType, FilterType, WrapMode);
};

}
