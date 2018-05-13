#include "GSPng.h"
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
    while (!src.atEnd())
    {
        PngChunk *chunk = PngChunk::Create(src);
        ReturnFailOnFail(chunk != NULL);
        m_chunks.append(chunk);
    }
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

}

int GSPng::Height() const
{

}

QImage GSPng::Image() const
{

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
