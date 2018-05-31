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

bool IDATChunk::Read(QDataStream &src, quint32 length)
{
    ReturnFailOnFail(PngChunk::Read(src, length));
    m_imageData = qUncompress(m_data);
    return true;
}

QByteArray IDATChunk::GetData() const
{
    return qCompress(m_imageData);
}
