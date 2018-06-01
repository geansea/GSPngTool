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
    PngColorType GetColorType() const;
    int GetCompressionMethod() const;
    int GetFilterMethod() const;
    int GetInterlaceMethod() const;

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    qint32 m_width;
    qint32 m_height;
    qint8 m_bitDepth;
    qint8 m_colorType;
    qint8 m_compressionMethod;
    qint8 m_filterMethod;
    qint8 m_interlaceMethod;
};

#endif // IHDRCHUNK_H
