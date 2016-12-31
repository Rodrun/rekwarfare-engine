/*
* Collection of datatypes and functions that modify the screen (e.g. render
*  primitive types, render textures, load textures, render text).
*/
#pragma once

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"

#include <string>

namespace rekwarfare {
/*
* The filter type tells loadTexture() how you want the texture you are loading
*  to be filtered. NEAREST results in a more pixelated-look, LINEAR gives a
*  blurrier, but non-pixelated look. (NEAREST would be best choice for
*  8-bit-like graphics).
* If OpenGL 3+ is enabled, then you have the choice to use mipmaps.
* NOTE: that the min filter is to have the desired mipmap filter, not the mag.
*/
typedef GLint FilterType;
extern const FilterType NEAREST;
extern const FilterType LINEAR;
// Mipmaps are supported in OpenGL versions 3.0+
/* Equivalent to GL_LINEAR_MIPMAP_NEAREST. */
extern const FilterType MIPMAP_LINEAR_NEAREST;
/* Equivalent to GL_NEAREST_MIPMAP_NEAREST. */
extern const FilterType MIPMAP_NEAREST_NEAREST;
/* Equivalent to GL_NEAREST_MIPMAP_LINEAR. */
extern const FilterType MIPMAP_NEAREST_LINEAR;
/* Equivalent to GL_LINEAR_MIPMAP_LINEAR. */
extern const FilterType MIPMAP_LINEAR_LINEAR;

typedef GLint WrapMode;
/* Equivalent to GL_REPEAT. */
extern const WrapMode REPEAT;
/* Equivalent to GL_MIRRORED_REPEAT. */
extern const WrapMode MIRROR_REPEAT;
/* Equivalent to GL_CLAMP_TO_EDGE. */
extern const WrapMode CLAMP_EDGE;
/* Equivalent to GL_CLAMP_TO_BORDER. */
extern const WrapMode CLAMP_BORDER;

typedef TTF_Font Font;
/*
* Short for Texture ID.
*/
typedef GLuint Tid;

/*
* Structure containing 2 dimensions
*/
typedef struct {
    int w, h;
} Dimension2i;

/*
* Struct containing RGBA values for a color. Should use color_X functions to
*  modify values to ensure valid numbers.
*/
struct Color {
    float r;
    float g;
    float b;
    float a;
    SDL_Color operator()();
    bool operator==(Color) const;
};
typedef struct Color Color;

// Predefined colors
extern const Color NO_COLOR;
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color WHITE;
/*
* Increase the color value, recommended use.
*/
void color_increase(float& c, float i);
/*
* Decrease the color value, recommended use.
*/
void color_decrease(float& c, float d);
/*
* Set the color value, recommended use.
*/
void color_set(float& c, float s);

/*
* Texture flip.
* NOFLIP - Normal texture, no flip.
* VERTICAL - Vertical flip (center Y axis flip).
* HORIZONTAL - Horizontal flip (center X axis flip).
*/
enum Flip { NOFLIP, VERTICAL, HORIZONTAL };
/*
* Modes of text rendering. SOLID is faster than BLENDED, but BLENDED gives
*  higher-quality looking results.
*/
enum TextRenderMode { SOLID, BLENDED };
/*
* Type of text to render.
*/
enum TextMode { LATIN1, UTF8 };
/*
* Validate a min filter. Will make sure the filter is supported.
*/
FilterType validateFilter(FilterType t);
/*
* Load a SDL_Surface from given path.
* returns: true on success, false otherwise.
*/
SDL_Surface* loadSurface(std::string path);
/*
* Free an SDL_Surface.
*/
void freeSurface(SDL_Surface*&);
/*
* Load a font.
* ptsize: Point size.
* index: Font face from the file. (if it contains multiple)
*/
Font* loadFont(std::string path, int ptsize, long index=0);
/*
* Free a font.
*/
void deleteFont(Font*);
/*
* Sets font kerning.
*/
void setFontKerning(Font*, bool);
int getFontHeight(const Font*);
/*
* Distance from the top of the font to the baseline.
*/
int getFontAscent(const Font*);
/*
* Distance from the baseline to the bottom of the font.
*/
int getFontDescent(const Font*);
/*
* Get width and height of a given string with a given font.
* returns: A Dimension2i struct containing width and height.
*/
Dimension2i getSizeOfString(Font* f, std::string s);
// Basic geometry (except triangle?!)
void drawRectangle(double x, double y, double w, double h, double rotation,
    Color);
void drawLine(double x1, double y1, double x2, double y2, double rotation,
    Color);
void drawPoint(double x, double y, Color);
/*
* Render a string in either LATIN1 or UTF8 (default UTF8).
* s: String to render.
* f: Font.
* r: Rendering mode, see TextRenderMode for documentation.
* m: LATIN1 or UTF8.
* min: Filter, see FilterType.
* mag: Filter, see FilterType.
*/
void drawText(std::string s, Font* f, double x, double y, double w, double h,
    double rotation, Color c, TextRenderMode r, TextMode m=UTF8,
    FilterType min=-1, FilterType mag=-1);
void drawText_shaded(std::string s, Font* f, double x, double y, double w,
    double h, double rotation, Color fg, Color bg, TextMode=UTF8,
    FilterType min=-1, FilterType mag=-1);
/*
* Set the default wrapping mode. This is used when UV coordinates for textures
*  are out of range.
*/
void setWrappingMode(WrapMode);
/*
* Set the default min filter for texture rendering.
*/
void setDefaultMinFilterType(FilterType);
/*
* Set the default mag filter for texture rendering.
*/
void setDefaultMagFilterType(FilterType);
/*
* Get the current/default wrapping mode.
*/
WrapMode getWrappingMode();
/*
* Get the default min filter for texture rendering.
*/
FilterType getDefaultMinFilterType();
/*
* Get the default mag filter for texture rendering.
*/
FilterType getDefaultMagFilterType();
/*
* Translate the display matrix x and y units.
*/
void translateScreen(double x, double y);
/*
* Wrapper for glPushMatrix().
*/
void pushMatrix();
/*
* Wrapper for glPopMatrix().
*/
void popMatrix();

}
