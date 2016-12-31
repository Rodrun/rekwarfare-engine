#include "Texture.hpp"

namespace rekwarfare {

Texture::Texture(SDL_Surface* s, FilterType min, FilterType mag, WrapMode wm) {
    loadTextureFromSurface(s, min, mag, wm);
}

Texture::Texture(std::string path, FilterType min, FilterType mag, WrapMode wm)
    {
    loadTexture(path, min, mag);
}

Texture::~Texture() {
    free();
}

void Texture::free() {
    glDeleteTextures(1, &mid);
    SDL_FreeSurface(msurface.get());
}

void Texture::loadTextureGL(SDL_Surface* surface, FilterType min,
    FilterType mag, WrapMode wrap_mode) {
    if (surface == nullptr) return;
    glGenTextures(1, &mid);
    glBindTexture(GL_TEXTURE_2D, mid);

    // Set correct color format
    auto colorfmt = (surface->format->BytesPerPixel == 4) ?  GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, colorfmt, surface->w, surface->h, 0,
        colorfmt, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
    // Make sure filters cope well with OpenGL context
    FilterType vmin = validateFilter(min);
    FilterType vmag = validateFilter(mag);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, vmin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, vmag);

    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::loadTexture(std::string path, FilterType min, FilterType mag,
    WrapMode wm) {
    SDL_Surface* sf = loadSurface(path);
    if (sf == nullptr) {
        SDL_FreeSurface(sf);
        return false;
    }

    mimg_width = sf->w;
    mimg_height = sf->h;

    loadTextureGL(sf, min, mag, wm);
    return true;
}

bool Texture::loadTextureFromSurface(SDL_Surface* s, FilterType min,
    FilterType mag, WrapMode wm) {
    if (s == nullptr)
        return false;
    loadTextureGL(s, min, mag, wm);
    return true;
}

void Texture::render(double x, double y, double w, double h,
    unsigned int tx, unsigned int ty, unsigned int tw, unsigned int th,
    double rotation, Color c, Flip f) const {
    glPushMatrix();
    if (rotation != 0){
        glTranslated(x + w / 2, y + h / 2, 0);
        glRotated(rotation, 0, 0, 1);
        glTranslated(-(x + w / 2), -(y + h / 2), 0);
    }

    float left = (float) tx / (float) mimg_height;
    float right = ((float) tx + (float) tw) / (float) mimg_width;
    float top = (float) ty / (float) mimg_height;
    float bottom = ((float) ty + (float) th) / (float) mimg_height;
    // "Normalize" them
    if (left > 1)    left    = 1; if (left < 0)     left   = 0;
    if (right > 1)   right   = 1; if (right < 0)    right  = 0;
    if (top > 1)     top     = 1; if (top < 0)      top    = 0;
    if (bottom > 1)  bottom  = 1; if (bottom < 0)   bottom = 0;

    glBindTexture(GL_TEXTURE_2D, mid);

    glBegin(GL_QUADS);
        if (!(c.r < 0 || c.g < 0 || c.b < 0 || c.a < 0))
            glColor4f(c.r, c.g, c.b, c.a);
        // bit of a blocky mess but it'll do for now...
        if (f == NOFLIP) {
            glTexCoord2f(left, top);
            glVertex2d(x, y);
            glTexCoord2f(right, top);
            glVertex2d(x + w, y);
            glTexCoord2f(right, bottom);
            glVertex2d(x + w, y + h);
            glTexCoord2f(left, bottom);
            glVertex2d(x, y + h);
        } else if (f == HORIZONTAL) {
            glTexCoord2f(left, top);
            glVertex2d(x, y + h);
            glTexCoord2f(right, top);
            glVertex2d(x + w, y + h);
            glTexCoord2f(right, bottom);
            glVertex2d(x + w, y);
            glTexCoord2f(left, bottom);
            glVertex2d(x, y);
        } else if (f == VERTICAL) {
            glTexCoord2f(left, top);
            glVertex2d(x + w, y);
            glTexCoord2f(right, top);
            glVertex2d(x, y);
            glTexCoord2f(right, bottom);
            glVertex2d(x, y + h);
            glTexCoord2f(left, bottom);
            glVertex2d(x + w, y + h);
        }
    glEnd();
#if 0
    const GLfloat UV[8] = {
        // Counter clock-wise
        // 0, 0, is the lower left, 1, 1 is top right
        left, bottom, // Lower Left
        right, bottom, // Lower right
        right, top, // Top Right
        left, top // Top Left
    };

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE_2D);
    glTexCoordPointer(2, GL_DOUBLE, 0, &UV);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void Texture::render(double x, double y, double w, double h,
    double rotation, Color c, Flip f) const {
    render(x, y, w, h, 1, 1, mimg_width, mimg_height, rotation, c, f);
}

}
