#include "PngChunk.h"
#include "PngChunk_IHDR.h"
#include <zlib.h>

PngChunk * PngChunk::Create(QDataStream &src)
{
    quint32 length = 0;
    qint32 type = 0;
    src >> length >> type;
    PngChunk *chunk = NULL;
    if (type == IHDR)
    {
        chunk = new PngChunk_IHDR(length, type);
    }
    else
    {
        chunk = new PngChunk(length, type);
    }
    if (chunk == NULL)
    {
        return NULL;
    }
    if (!chunk->Read(src))
    {
        delete chunk;
        return NULL;
    }
    if (!chunk->IsValid())
    {
        delete chunk;
        return NULL;
    }
    return chunk;
}

PngChunk::PngChunk(quint32 length, qint32 type)
    : m_length(length)
    , m_type(type)
    , m_data((int)length, 0)
    , m_crc(0)
{
}

PngChunk::~PngChunk()
{
}

int PngChunk::Type() const
{
    return (int)m_type;
}

bool PngChunk::Read(QDataStream &src)
{
    src.readRawData(m_data.data(), m_data.size());
    src >> m_crc;
    return QDataStream::Status::Ok == src.status();
}

bool PngChunk::IsValid() const
{
    return (int)m_length == m_data.size() && m_crc == ValidCRC();
}

quint32 PngChunk::ValidCRC() const
{
    uLong crc = 0;
    //crc = crc32(crc, &m_type);
    crc = crc32(crc, (const Bytef *)m_data.data(), (uInt)m_data.size());
    return (quint32)crc;
}

int PngChunk::Size() const
{
    return sizeof(m_length) + sizeof(m_type) + m_data.size() + sizeof(m_crc);
}

bool PngChunk::Write(QDataStream &dst)
{
    dst << m_length;
    dst << m_type;
    dst.writeRawData(m_data.data(), m_data.size());
    dst << m_crc;
    return QDataStream::Status::Ok == dst.status();
}
