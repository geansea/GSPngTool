#ifndef IHDRCHUNK_H
#define IHDRCHUNK_H

#include "PngChunk.h"

class IHDRChunk : public PngChunk
{
public:
    IHDRChunk();
    virtual ~IHDRChunk();

public:
    int GetWidth() const;
    int GetHeight() const;
    int GetBitDepth() const;
    PngColorMode GetColorMode() const;
    int GetCompressionMethod() const;
    int GetFilterMethod() const;
    int GetInterlaceMethod() const;

protected:
    virtual bool LoadData();
    virtual void UpdateData();

private:
    qint32 m_width;
    qint32 m_height;
    qint8 m_bitDepth;
    qint8 m_colorMode;
    qint8 m_compressionMethod;
    qint8 m_filterMethod;
    qint8 m_interlaceMethod;
};

#endif // IHDRCHUNK_H
