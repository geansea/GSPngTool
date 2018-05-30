#include "IHDRChunk.h"

#define CHUNK_LENGTH 0x0D

IHDRChunk::IHDRChunk()
    : PngChunk(IHDR)
    , m_width(0)
    , m_height(0)
    , m_bitDepth(0)
    , m_colorMode(0)
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

PngColorMode IHDRChunk::GetColorMode() const
{
    switch (m_colorMode)
    {
    case PngGrayscale:
        return PngGrayscale;
    case PngTruecolor:
        return PngTruecolor;
    case PngPaletteBased:
        return PngPaletteBased;
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

bool IHDRChunk::Read(QDataStream &src, quint32 length)
{
    ReturnFailOnFail(length == CHUNK_LENGTH);
    src >> m_width;
    src >> m_height;
    src >> m_bitDepth;
    src >> m_colorMode;
    src >> m_compressionMethod;
    src >> m_filterMethod;
    src >> m_interlaceMethod;
    return QDataStream::Status::Ok == src.status();
}

QByteArray IHDRChunk::GetData() const
{
    QByteArray data(CHUNK_LENGTH, 0);
    QDataStream dst(&data, QIODevice::WriteOnly);
    dst << m_width;
    dst << m_height;
    dst << m_bitDepth;
    dst << m_colorMode;
    dst << m_compressionMethod;
    dst << m_filterMethod;
    dst << m_interlaceMethod;
    return data;
}
