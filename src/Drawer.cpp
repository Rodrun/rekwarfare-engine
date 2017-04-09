#include "Drawer.hpp"

#include "Texture.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"

#include <string>

namespace rekwarfare {

const GLint NEAREST = GL_NEAREST;
const GLint LINEAR = GL_LINEAR;
const Color NO_COLOR = { -1, -1, -1, -1 };
const Color RED = { 1, 0, 0, 1 };
const Color GREEN = { 0, 1, 0, 1 };
const Color BLUE = { 0, 0, 1, 1 };
const Color WHITE = { 1, 1, 1, 1 };
const WrapMode REPEAT = GL_REPEAT;
const WrapMode MIRROR_REPEAT = GL_MIRRORED_REPEAT;
const WrapMode CLAMP_EDGE = GL_CLAMP_TO_EDGE;
const WrapMode CLAMP_BORDER = GL_CLAMP_TO_BORDER;
const FilterType MIPMAP_LINEAR_NEAREST = GL_LINEAR_MIPMAP_NEAREST;
const FilterType MIPMAP_NEAREST_NEAREST = GL_NEAREST_MIPMAP_NEAREST;
const FilterType MIPMAP_NEAREST_LINEAR = GL_NEAREST_MIPMAP_LINEAR;
const FilterType MIPMAP_LINEAR_LINEAR = GL_LINEAR_MIPMAP_LINEAR;

namespace {
    /* The default wrap mode, can be changed with setWrappingMode(). */
    WrapMode wrap_mode = REPEAT;
    /*
    * Default min and mag filters. Separate due to the fact that min filter
    *  should be the only one with a mipmap filter value.
    */
    FilterType default_filter_min = NEAREST;
    FilterType default_filter_mag = NEAREST;
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
    * Load a texture from given surface, which should contain TTF information,
    *  and then render the string.
    */
    void loadAndRenderText(SDL_Surface* sf, double x, double y, double w,
        double h, double rotation, Color c, FilterType min, FilterType mag) {
        Texture t(sf, min, mag);
        t.render(x, y, w, h, rotation, c);
    }
    /*
    * Normalize the given color value, if not already.
    */
    void validateColor(float& c) {
        if (c > 1 || c < 0) {
            if (c > 1)
                c = 1;
            else if (c < 0)
                c = 0;
        }
    }
}

SDL_Color Color::operator()() {
    SDL_Color retc = { convertColor_uint(r), convertColor_uint(g),
        convertColor_uint(b), convertColor_uint(a) };
    return retc;
}

bool Color::operator==(Color other) const {
    return (other.r == r && other.g == g && other.b == b && other.a == a);
}

void color_increase(float& c, float i) {
    c += i;
    validateColor(c);
}

void color_decrease(float& c, float d) {
    c -= d;
    validateColor(c);
}

void color_set(float& c, float s) {
    c = s;
    validateColor(c);
}

FilterType validateFilter(FilterType t) {
    int version;
    // Check if context is OpenGL 3.0 or higher
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &version);
    if (version <= 3 && (t != LINEAR || t != NEAREST)) {
        // Mipmaps aren't supported in versions before 3.0
        if (t == MIPMAP_LINEAR_LINEAR || t == MIPMAP_LINEAR_NEAREST)
            return LINEAR;
        else
            return NEAREST;
    }
    return t;
}

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* s = IMG_Load(path.c_str());
    if (s == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
            "Couldn't load %s, reason: %s", path.c_str(), IMG_GetError());
        return nullptr;
    }
    return s;
}

void freeSurface(SDL_Surface*& sf) {
    SDL_FreeSurface(sf);
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

void drawRectangle(double x, double y, double w, double h, double rotation,
    Color c) {
    glPushMatrix();

    if (rotation != 0){
        glTranslated(x + w / 2, y + h / 2, 0);
        glRotated(rotation, 0, 0, 1);
        glTranslated(-(x + w / 2), -(y + h / 2), 0);
    }
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
    float colors[] = {
        c.r, c.g, c.b, c.a, c.r, c.g, c.b, c.a,
        c.r, c.g, c.b, c.a, c.r, c.g, c.b, c.a,
        c.r, c.g, c.b, c.a, c.r, c.g, c.b, c.a,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_DOUBLE, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

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

    const float colors[] = { c.r, c.g, c.b, c.a, c.r, c.g, c.b, c.a };
    const double verts[4] = { x1, y1, x2, y2 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_DOUBLE, 0, verts);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPopMatrix();
}

void drawPoint(double x, double y, Color c) {
    const float color[] = { c.r, c.g, c.b, c.a };
    const double vert[2] = { x, y };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_DOUBLE, 0, vert);
    glColorPointer(4, GL_FLOAT, 0, color);
    glDrawArrays(GL_POINTS, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
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
    loadAndRenderText(sf, x, y, w, h, rotation, NO_COLOR, min, mag);
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
    SDL_FreeSurface(sf);
}

void setWrappingMode(WrapMode m) {
    wrap_mode = m;
}

void setDefaultMinFilterType(FilterType t) {
    default_filter_min = validateFilter(t);
}

void setDefaultMagFilterType(FilterType t) {
    default_filter_mag = validateFilter(t);
}

WrapMode getWrappingMode() {
    return wrap_mode;
}

FilterType getDefaultMinFilterType() {
    return default_filter_min;
}

FilterType getDefaultMagFilterType() {
    return default_filter_mag;
}

void translateScreen(double x, double y) {
    glTranslated(x, y, 0);
}

void pushMatrix() {
    glPushMatrix();
}

void popMatrix() {
    glPopMatrix();
}

}
