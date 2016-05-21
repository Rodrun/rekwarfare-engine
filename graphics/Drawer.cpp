#include "Drawer.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_opengl.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <vector>

namespace rekwarfare {

const GLint NEAREST = GL_NEAREST;
const GLint LINEAR = GL_LINEAR;
const Color NO_COLOR = { -1, -1, -1, -1 };

namespace {
    Tid last_tex_id = -1;
    /*
    * Convert a float-based color value to a uint8-based color value.
    */
    Uint8 convertColor_uint(float f) {
        if (f <= 0)
            return 0;
        else if (f >= 1)
            return 255;
        return (Uint8)(255 * f);
    }
    /*
    * Call proper GL functions to load a texture.
    * id: Texture id to be set.
    * min: See loadTexture min and mag documentation.
    */
    void loadTextureGL(SDL_Surface* surface, Tid& id, FilterType min,
        FilterType mag) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        auto colorfmt = GL_RGB;
        if (surface->format->BytesPerPixel == 4) {
            colorfmt = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, colorfmt, surface->w, surface->h, 0,
            colorfmt, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

//        SDL_FreeSurface(surface);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    /*
    * Load a texture from given surface, which should contain TTF information,
    *  and then render the string.
    */
    void loadAndRenderText(SDL_Surface* sf, double x, double y, double w,
        double h, double rotation, Color c, FilterType min, FilterType mag) {
        Texture t;
        if (loadTextureFromSurface(t, sf, min, mag)) {
            drawTexture(t, x, y, w, h, rotation, c);
        }
    }
}

SDL_Color Color::operator()() {
    SDL_Color retc = { convertColor_uint(r), convertColor_uint(g),
        convertColor_uint(b), convertColor_uint(a) };
    return retc;
}

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
    if (!loadSurface(t.surface, path)) return false;

    t.img_width = t.surface->w;
    t.img_height = t.surface->h;

    loadTextureGL(t.surface, t.id, min, mag);
    return true;
}

bool loadSurface(SDL_Surface*& s, std::string path) {
    s = IMG_Load(path.c_str());
    if (s == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't load %s, reason: %s", path.c_str(), IMG_GetError());
        return false;
    }
    return true;
}

bool loadTextureFromSurface(Texture& t, SDL_Surface* s, FilterType min,
    FilterType mag) {
    if (s == nullptr)
        return false;
    loadTextureGL(s, t.id, min, mag);
    return true;
}

void deleteTexture(Texture& t) {
    glDeleteTextures(1, &t.id);
    SDL_FreeSurface(t.surface);
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
// TODO: Implement vertex arrays to use over immediate mode
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

    #ifdef REKWARFARE_USE_IMMEDIATEMODE
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
    #else

    #endif
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
    #ifndef REKWARFARE_USE_VERTARRAYS

    glBegin(GL_TRIANGLES);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2d(x, y);
        glVertex2d(x + w, y);
        glVertex2d(x + w, y + h);

        glVertex2d(x + w, y + h);
        glVertex2d(x, y + h);
        glVertex2d(x, y);
    glEnd();
    #else
    const GLdouble vertices[12] = {
        // Bottom left
        x, y,
        x, y + h,
        x + w, y + h,
        // Top right
        x + w, y + h,
        x + w, y,
        x, y
    };
    std::vector<float> colors;
    // 12 * 4 = vertices length * 4 (rgba)
    for (auto i = 0; i < (12 * 4); i++) {
        colors.push_back(c.r);
        colors.push_back(c.g);
        colors.push_back(c.b);
        colors.push_back(c.a);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    #endif
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

void drawText(std::string s, Font* f, double x, double y, double w, double h,
    double rotation, Color c, TextRenderMode r, TextMode m, FilterType min,
    FilterType mag) {
    SDL_Surface* sf = nullptr;
    switch (r) {
        case SOLID:
            if (m == UTF8)
                sf = TTF_RenderUTF8_Solid(f, s.c_str(), c());
            else
                sf = TTF_RenderText_Solid(f, s.c_str(), c());
            break;
        case BLENDED:
            if (m == UTF8)
                sf = TTF_RenderUTF8_Blended(f, s.c_str(), c());
                else
                sf = TTF_RenderText_Blended(f, s.c_str(), c());
            break;
    }
    loadAndRenderText(sf, x, y, w, h, rotation, c, min, mag);
    SDL_FreeSurface(sf);
}

void drawText_shaded(std::string s, Font* f, double x, double y, double w,
    double h, double rotation, Color fg, Color bg, TextMode m, FilterType min,
    FilterType mag) {
    SDL_Surface* sf = nullptr;
    if (m == UTF8)
        sf = TTF_RenderUTF8_Shaded(f, s.c_str(), fg(), bg());
    else
        sf = TTF_RenderText_Shaded(f, s.c_str(), fg(), bg());

    loadAndRenderText(sf, x, y, w, h, rotation, NO_COLOR, min, mag);
}

}
