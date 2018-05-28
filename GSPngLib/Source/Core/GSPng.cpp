#include "GSPng.h"
#include "PngHelper.h"
#include "PngDef.h"

IGSPng * IGSPng::CreateFromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return NULL;
    }
    GSPng *png = new GSPng();
    if (png != NULL)
    {
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::BigEndian);
        png->Open(stream);
    }
    file.close();
    return png;
}

GSPng::GSPng()
    : m_chunks()
{
}

GSPng::~GSPng()
{
    Close();
}

bool GSPng::Open(QDataStream &src)
{
    Close();
    src.setByteOrder(QDataStream::BigEndian);
    QByteArray header(PngHelper::HEADER.size(), 0);
    src.readRawData(header.data(), header.size());
    ReturnFailOnFail(PngHelper::HEADER == header);
    do
    {
        PngChunk *chunk = PngChunk::Create(src);
        ReturnFailOnFail(chunk != NULL);
        m_chunks.append(chunk);
    } while (!src.atEnd());
    ReturnFailOnFail(m_chunks.size() > 0);
    return true;
}

void GSPng::Close()
{
    foreach (PngChunk *chunk, m_chunks)
    {
        SafeDelete(chunk);
    }
    m_chunks.clear();
}

int GSPng::Size() const
{
    int size = 0;
    foreach (PngChunk *chunk, m_chunks)
    {
        int chunkSize = chunk->Size();
        size += chunkSize;
    }
    return size;
}

int GSPng::Width() const
{
    return 0;
}

int GSPng::Height() const
{
    return 0;
}

QImage GSPng::Image() const
{
    return QImage();
}

PngChunk * GSPng::GetChunk(enum PngChunk::Type type) const
{
    PngChunk *ret = NULL;
    foreach (PngChunk *chunk, m_chunks)
    {
        if (chunk->Type() == type)
        {
            ret = chunk;
            break;
        }
    }
    return ret;
}
