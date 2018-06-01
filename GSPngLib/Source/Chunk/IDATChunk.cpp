#include "IDATChunk.h"

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
    ReturnFailOnFail(PngChunk::LoadData());
    m_imageData = qUncompress(m_data);
    return true;
}

bool IDATChunk::UpdateData()
{
    m_data = qCompress(m_imageData);
    ReturnFailOnFail(PngChunk::UpdateData());
    return true;
}
