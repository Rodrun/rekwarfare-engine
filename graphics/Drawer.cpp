#include "Drawer.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_opengl.h"
#include "SDL2/SDL_ttf.h"

#include <string>

namespace rekwarfare {

GLuint last_tex_id = 0;

void color_increase(float& c, float i) {
    if (!(i > 1) || !(i < 0))
        c += i;
    if (c > 1)
        c = 1;
    else if (c < 0)
        c = 0;
}

void color_decrease(float& c, float d) {
    if (!(d > 1) || !(d < 0))
        c -= d;
    if (c > 1)
        c = 1;
    else if (c < 0)
        c = 0;
}

bool loadTexture(Texture& t, std::string path, FilterType min, FilterType mag) {
    t.surface = IMG_Load(path.c_str());
    if (t.surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't load %s, reason: %s", path.c_str(), IMG_GetError());
        return false;
    }

    t.img_width = t.surface->w;
    t.img_height = t.surface->h;

    glGenTextures(1, &t.id);
    glBindTexture(GL_TEXTURE_2D, t.id);

    auto colorfmt = GL_RGB;
    if (t.surface->format->BytesPerPixel == 4) {
        colorfmt = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, colorfmt, t.surface->w, t.surface->h, 0,
        colorfmt, GL_UNSIGNED_BYTE, t.surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

    SDL_FreeSurface(t.surface);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void deleteTexture(Texture& t) {
    glDeleteTextures(1, &t.id);
}

Font* loadFont(std::string path, int ptsize, long index) {
    Font* f = TTF_OpenFontIndex(path.c_str(), ptsize, index);
    if (!f) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't load font %s, reason: %s", path.c_str(), TTF_GetError());
        return nullptr;
    }
    return f;
}

void deleteFont(Font* f) {
    TTF_CloseFont(f);
}

void setFontKerning(Font* f, bool k) {
    TTF_SetFontKerning(f, (k) ? 1 : 0);
}

int getFontHeight(const Font* f) {
    return TTF_FontHeight(f);
}

int getFontAscent(const Font* f) {
    return TTF_FontAscent(f);
}

Dimension2i getSizeOfString(Font* f, std::string s) {
    Dimension2i d = { 0, 0 };
    if (f != nullptr) {
        TTF_SizeText(f, s.c_str(), &d.w, &d.h);
    }
    return d;
}

void drawTexture(Texture t, double x, double y, double w, double h,
    unsigned int tx, unsigned int ty, unsigned int tw, unsigned int th,
    double rotation, Color c) {
    if (t.id != last_tex_id) { // to minimalize gl calls as much as possible
        glBindTexture(GL_TEXTURE_2D, t.id);
    } else {
        last_tex_id = t.id;
    }

    glPushMatrix();
    if (rotation != 0){
        glTranslated(x + w / 2, y + h / 2, 0);
        glRotated(rotation, 0, 0, 1);
        glTranslated(-(x + w / 2), -(y + h / 2), 0);
    }

    float left = (float) tx / (float) t.img_height;
    float right = ((float) tx + (float) tw) / (float) t.img_width;
    float top = (float) ty / (float) t.img_height;
    float bottom = ((float) ty + (float) th) / (float) t.img_height;
    // "Normalize" them
    if (left > 1)    left    = 1; if (left < 0)     left = 0;
    if (right > 1)   right   = 1; if (right < 0)    right = 0;
    if (top > 1)     top     = 1; if (top < 0)      top = 0;
    if (bottom > 1)  bottom  = 1; if (bottom < 0)   bottom = 0;

    glBegin(GL_QUADS);
        if (!(c.r < 0 || c.g < 0 || c.b < 0 || c.a < 0))
            glColor4f(c.r, c.g, c.b, c.a);
        glTexCoord2f(left, top);
        glVertex2d(x, y);
        glTexCoord2f(right, top);
        glVertex2d(x + w, y);
        glTexCoord2f(right, bottom);
        glVertex2d(x + w, y + h);
        glTexCoord2f(left, bottom);
        glVertex2d(x, y + h);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawTexture(Texture t, double x, double y, double w, double h,
    double rotation, Color c) {
    drawTexture(t, x, y, w, h, 1, 1, t.img_width, t.img_height, rotation, c);
}

void drawRectangle(double x, double y, double w, double h, double rotation,
    Color c) {
    glPushMatrix();

    if (rotation != 0){
        glTranslated(x + w / 2, y + h / 2, 0);
        glRotated(rotation, 0, 0, 1);
        glTranslated(-(x + w / 2), -(y + h / 2), 0);
    }

    glBegin(GL_TRIANGLES);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2d(x, y);
        glVertex2d(x + w, y);
        glVertex2d(x + w, y + h);

        glVertex2d(x + w, y + h);
        glVertex2d(x, y + h);
        glVertex2d(x, y);
    glEnd();
    glPopMatrix();
}

void drawLine(double x1, double y1, double x2, double y2, double rotation,
    Color c) {
    glPushMatrix();

    if (rotation != 0){
        glTranslated(x1 + x2 / 2, y1 + y2 / 2, 0);
        glRotated(rotation, 0, 0, 1);
        glTranslated(-(x1 + x2 / 2), -(y1 + y2 / 2), 0);
    }

    glBegin(GL_LINES);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
    glPopMatrix();
}

void drawText(Font* f, double x, double y, double w, double h, double rotation,
    Color, TypeText g) {
    switch (g.type) {
        case LATIN1:

            break;
        case UTF8:

            break;
        case UNICODE:

            break;
        case UNICODE_GLYPH:

            break;
    }
}

}
