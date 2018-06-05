#include "IDATChunk.h"

IDATChunk::IDATChunk()
    : PngChunk(IDAT)
{
}

IDATChunk::~IDATChunk()
{
}

QByteArray IDATChunk::GetImageData() const
{
    return qUncompress(m_data);
}

void IDATChunk::SetImageData(const QByteArray &imageData)
{
    m_data = qCompress(imageData);
}
