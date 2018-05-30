#ifndef PNGDEF_H
#define PNGDEF_H

#include "GSDef.h"

enum PngColorMode
{
    PngGrayscale = 0,
    PngTruecolor = 2,
    PngPaletteBased = 3,
    PngGrayscaleWithAlpha = 4,
    PngTruecolorWithAlpha = 6,
    PngColorModeUnknown = -1
};

#endif // PNGDEF_H
