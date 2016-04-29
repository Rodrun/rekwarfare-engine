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
/*
* Short for Texture ID.
*/
typedef GLuint Tid;

typedef struct {
    float r;
    float g;
    float b;
    float a;
    SDL_Color operator()();
} Color;

extern const Color NO_COLOR;

typedef struct {
    int w;
    int h;
} Dimension2i;

void color_increase(float& c, float i);
void color_decrease(float& c, float d);

typedef struct {
    Tid id = 0;
    /* Image's width and height */
    unsigned int img_width;
    unsigned int img_height;
    // Shouldn't be touched.
    SDL_Surface* surface = nullptr;
} Texture;

/*
* Modes of (text) rendering. Ordered from fastest to slowest.
*/
enum TextRenderMode { SOLID, /*SHADED,*/ BLENDED }; // Omit SHADED!
/*
* Type of text to render.
*/
enum TextMode { LATIN1, UTF8 };

/*
* Load a texture.
* t: Reference to the texture you want to set.
* min: GL_TEXTURE_MIN_FILTER value. (texture sized down)
* mag: GL_TEXTURE_MAG_FILTER value. (texture enlarged)
* returns: true if loading was successful, false otherwise.
*/
bool loadTexture(Texture& t, std::string path, FilterType min=LINEAR,
    FilterType mag=LINEAR);
bool loadSurface(SDL_Surface*&, std::string path);
/*
* Load a texture from an SDL_Surface.
* t: Reference to the texture you want to set.
* s: SDL_Surface with image information.
* min: GL_TEXTURE_MIN_FILTER value. (texture sized down)
* mag: GL_TEXTURE_MAG_FILTER value. (texture enlarged)
* returns: true if loading was successful, false otherwise.
*/
bool loadTextureFromSurface(Texture& t, SDL_Surface* s, FilterType min,
    FilterType mag);
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
/*
* Render a string in either LATIN1 or UTF8 (default UTF8).
* s: String to render.
* f: Font.
* r: Rendering mode, see TextRenderMode for documentation.
* m: LATIN1 or UTF8.
*/
void drawText(std::string s, Font* f, double x, double y, double w, double h,
        double rotation, Color c, TextRenderMode r, TextMode m=UTF8);
void drawText_shaded(std::string s, Font* f, double x, double y, double w,
    double h, double rotation, Color fg, Color bg, TextMode=UTF8);
}
