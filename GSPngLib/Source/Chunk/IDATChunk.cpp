#include "IDATChunk.h"
#include <zlib.h>

IDATChunk::IDATChunk()
    : PngChunk(IDAT)
    , m_imageData()
{
}

IDATChunk::~IDATChunk()
{
}

const QByteArray & IDATChunk::GetImageData() const
{
    return m_imageData;
}

bool IDATChunk::LoadData()
{
    PngChunk::LoadData();
    m_imageData = qUncompress(m_data);
    return true;
}

void IDATChunk::UpdateData()
{
    m_data = qCompress(m_imageData);
    PngChunk::UpdateData();
}
