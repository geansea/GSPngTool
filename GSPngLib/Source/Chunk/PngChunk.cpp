#include "PngChunk.h"
#include "IHDRChunk.h"
#include "PLTEChunk.h"
#include "Core/PngHelper.h"

PngChunk * PngChunk::Create(QDataStream &src)
{
    quint32 length = 0;
    qint32 type = 0;
    src >> length;
    src >> type;
    PngChunk *chunk = NULL;
    switch (type)
    {
    case IHDR:
        chunk = new IHDRChunk();
        break;
    case PLTE:
        chunk = new PLTEChunk();
        break;
    default:
        chunk = new PngChunk(type);
        break;
    }
    GSPointerScope<PngChunk> scope(chunk);
    ReturnNullOnFail(chunk->Read(src, length));
    quint32 crc = 0;
    src >> crc;
    ReturnNullOnFail(chunk->GetCRC() == crc);
    scope.Cancel();
    return chunk;
}

PngChunk::PngChunk(qint32 type)
    : m_type(type)
    , m_data()
    , m_dataChanged(false)
{
}

PngChunk::~PngChunk()
{
}

int PngChunk::GetType() const
{
    return m_type;
}

int PngChunk::GetSize() const
{
    return 4 + 4 + m_data.size() + 4;
}

bool PngChunk::Read(QDataStream &src, quint32 length)
{
    m_data.resize(length);
    src.readRawData(m_data.data(), m_data.size());
    ReturnFailOnFail(QDataStream::Status::Ok == src.status());
    ReturnFailOnFail(LoadData());
    return true;
}

bool PngChunk::Write(QDataStream &dst)
{
    if (m_dataChanged)
    {
        ReturnFailOnFail(UpdateData());
    }
    dst << m_data.size();
    dst << m_type;
    dst.writeRawData(m_data.data(), m_data.size());
    dst << GetCRC();
    ReturnFailOnFail(QDataStream::Status::Ok == dst.status());
    return true;
}

bool PngChunk::LoadData()
{
    return true;
}

bool PngChunk::UpdateData()
{
    m_dataChanged = false;
    return true;
}

quint32 PngChunk::GetCRC() const
{
    quint32 crc = 0;
    crc = PngHelper::UpdateCRC32(crc, PngHelper::IntToBytesBE(m_type));
    crc = PngHelper::UpdateCRC32(crc, m_data);
    return crc;
}
