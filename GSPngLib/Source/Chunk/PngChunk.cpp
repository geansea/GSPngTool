#include "PngChunk.h"
#include "IHDRChunk.h"
#include "Core/PngDef.h"
#include <zlib.h>

PngChunk * PngChunk::Create(QDataStream &src)
{
    quint32 length = 0;
    qint32 type = 0;
    src >> length >> type;
    PngChunk *chunk = NULL;
    switch (type)
    {
    case IHDR:
        chunk = new IHDRChunk();
        break;
    default:
        chunk = new PngChunk(type);
        break;
    }
    GSPointerScope<PngChunk> scope(chunk);
    ReturnNullOnFail(chunk->Read(src, length));
    quint32 crc = 0;
    src >> crc;
    ReturnNullOnFail(chunk->GetCRC() != crc);
    scope.Cancel();
    return chunk;
}

QByteArray IntToBytesBE(int value)
{
    QByteArray bytes(4, 0);
    bytes[0] = (char)((value >> 24) & 0xFF);
    bytes[1] = (char)((value >> 16) & 0xFF);
    bytes[2] = (char)((value >> 8) & 0xFF);
    bytes[3] = (char)(value & 0xFF);
    return bytes;
}

PngChunk::PngChunk(qint32 type)
    : m_type(type)
    , m_data()
{
}

PngChunk::~PngChunk()
{
}

int PngChunk::Type() const
{
    return (int)m_type;
}

int PngChunk::Size() const
{
    const QByteArray data = GetData();
    return 4 + 4 + data.size() + 4;
}

bool PngChunk::Write(QDataStream &dst) const
{
    const QByteArray typeBytes = IntToBytesBE(Type());
    const QByteArray data = GetData();
    quint32 crc = GetCRC();
    dst << data.size();
    dst.writeRawData(typeBytes.data(), typeBytes.size());
    dst.writeRawData(data.data(), data.size());
    dst << crc;
    return QDataStream::Status::Ok == dst.status();
}

bool PngChunk::Read(QDataStream &src, quint32 length)
{
    m_data.resize(length);
    src.readRawData(m_data.data(), m_data.size());
    return QDataStream::Status::Ok == src.status();
}

QByteArray PngChunk::GetData() const
{
    return m_data;
}

quint32 PngChunk::GetCRC() const
{
    const QByteArray typeBytes = IntToBytesBE(Type());
    const QByteArray data = GetData();
    uLong crc = 0;
    crc = crc32(crc, (const Bytef *)typeBytes.data(), (uInt)typeBytes.size());
    crc = crc32(crc, (const Bytef *)data.data(), (uInt)data.size());
    return (quint32)crc;
}
