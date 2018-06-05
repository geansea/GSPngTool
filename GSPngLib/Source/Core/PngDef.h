#ifndef PNGDEF_H
#define PNGDEF_H

#include "GSDef.h"
#include <QtGui>

// https://www.w3.org/TR/PNG/

enum PngColorType
{
    PngGrayscale = 0,
    PngTruecolor = 2,
    PngIndexedColor = 3,
    PngGrayscaleWithAlpha = 4,
    PngTruecolorWithAlpha = 6,
    PngColorModeUnknown = -1
};

#endif // PNGDEF_H
