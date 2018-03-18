#ifndef PNGCHUNK_IHDR_H
#define PNGCHUNK_IHDR_H

#include "PngChunk.h"

class PngChunk_IHDR : public PngChunk
{
public:
    PngChunk_IHDR(quint32 length, qint32 type);
    virtual ~PngChunk_IHDR();
};

#endif // PNGCHUNK_IHDR_H
