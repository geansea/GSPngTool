#include "IHDRChunk.h"

#define CHUNK_LENGTH 0x0D

IHDRChunk::IHDRChunk()
    : PngChunk(IHDR)
    , m_width(0)
    , m_height(0)
    , m_bitDepth(0)
    , m_colorType(0)
    , m_compressionMethod(0)
    , m_filterMethod(0)
    , m_interlaceMethod(0)
{
}

IHDRChunk::~IHDRChunk()
{
}

int IHDRChunk::GetWidth() const
{
    return m_width;
}

int IHDRChunk::GetHeight() const
{
    return m_height;
}

int IHDRChunk::GetBitDepth() const
{
    return m_bitDepth;
}

PngColorType IHDRChunk::GetColorType() const
{
    switch (m_colorType)
    {
    case PngGrayscale:
        return PngGrayscale;
    case PngTruecolor:
        return PngTruecolor;
    case PngIndexedColor:
        return PngIndexedColor;
    case PngGrayscaleWithAlpha:
        return PngGrayscaleWithAlpha;
    case PngTruecolorWithAlpha:
        return PngTruecolorWithAlpha;
    default:
        return PngColorModeUnknown;
    }
}

int IHDRChunk::GetCompressionMethod() const
{
    return m_compressionMethod;
}

int IHDRChunk::GetFilterMethod() const
{
    return m_filterMethod;
}

int IHDRChunk::GetInterlaceMethod() const
{
    return m_interlaceMethod;
}

bool IHDRChunk::LoadData()
{
    GSRFF(PngChunk::LoadData());
    GSRFF(m_data.size() == CHUNK_LENGTH);
    QDataStream src(m_data);
    src.setByteOrder(QDataStream::BigEndian);
    src >> m_width;
    src >> m_height;
    src >> m_bitDepth;
    src >> m_colorType;
    src >> m_compressionMethod;
    src >> m_filterMethod;
    src >> m_interlaceMethod;
    GSRFF(src.status() == QDataStream::Status::Ok);
    GSRFF(src.atEnd());
    return true;
}

bool IHDRChunk::UpdateData()
{
    m_data.resize(CHUNK_LENGTH);
    QDataStream dst(&m_data, QIODevice::WriteOnly);
    dst.setByteOrder(QDataStream::BigEndian);
    dst << m_width;
    dst << m_height;
    dst << m_bitDepth;
    dst << m_colorType;
    dst << m_compressionMethod;
    dst << m_filterMethod;
    dst << m_interlaceMethod;
    GSRFF(dst.status() == QDataStream::Status::Ok);
    GSRFF(dst.atEnd());
    GSRFF(PngChunk::UpdateData());
    return true;
}
