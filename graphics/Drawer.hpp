#pragma once

#include "SDL2/SDL.h"
#include "SDL_opengl.h"
#include "SDL2/SDL_ttf.h"

#include <string>

namespace rekwarfare {

/*
* The filter type tells loadTexture() how you want the texture you are loading
*  to be filtered. NEAREST results in a more pixelated-look, LINEAR gives a
*  blurrier, but non-pixelated look. (NEAREST would be best choice for
*  8-bit-like graphics)
* ... Yes, I'm using macros to define them...
*/
typedef GLint FilterType;
#define NEAREST GL_NEAREST
#define LINEAR GL_LINEAR

typedef TTF_Font Font;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct {
    int w;
    int h;
} Dimension2i;

void color_increase(float& c, float i);
void color_decrease(float& c, float d);

typedef struct {
    GLuint id;
    /* Image's width and height */
    unsigned int img_width;
    unsigned int img_height;
    // Shouldn't be touched.
    SDL_Surface* surface = nullptr;
} Texture;

/*
* Modes of rendering. Ordered from fastest to slowest.
*/
enum Mode { SOLID, SHADED, BLENDED };
enum TypeText { LATIN1, UTF8, UNICODE, UNICODE_GLYPH };

/*
* Holds information on how to render text.
*/
typedef struct {
    Mode mode;
    TypeText type;
} TextRender;

/*
* Load a texture.
* Texture&: Reference to the texture you want to set.
* min: GL_TEXTURE_MIN_FILTER value. (texture sized down)
* mag: GL_TEXTURE_MAG_FILTER value. (texture enlarged)
* returns: true if loading was successful, false otherwise.
*/
bool loadTexture(Texture&, std::string path, FilterType min=LINEAR,
    FilterType mag=LINEAR);
void deleteTexture(Texture&);
/*
* Load a font.
* ptsize: Point size.
* index: Font face from the file. (if it contains multiple)
*/
Font* loadFont(std::string path, int ptsize, long index=0);
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
/*
* Draw a section of a texture.
* NOTE: unless multiplybydim = false, will multiply tx/ty * tw/th to get
*  coordinates
* NOTE: To use original texture color, assign one(or more)of Color's members
*  to -1.
* tx/ty: Tile x/y
* tw/th: Tile width/height
* multiplybydim: Weather to multiply tx or ty by tw or th. Set to false if
*  specific tile coordinates are desired rather than the use of 1,2,3,4, etc...
*/
void drawTexture(Texture, double x, double y, /* uint? */ double w, double h,
    unsigned int tx, unsigned int ty, unsigned int tw, unsigned int th,
    double rotation, Color);
/*
* Draw a whole texture. Calls drawTexture() with tw & th being the size of the
*  whole texture, and tx & ty = 0.
* NOTE: To use original texture color, assign one(or more)of Color's members
*  to -1.
*/
void drawTexture(Texture, double x, double y, double w, double h,
    double rotation, Color);
void drawRectangle(double x, double y, double w, double h, double rotation,
    Color);
void drawLine(double x1, double y1, double x2, double y2, double rotation,
    Color);
void drawText(Font* f, double x, double y, double w, double h, double rotation,
    Color, TextRender g);
}
