#include "GSPng.h"
#include "Chunk/IHDRChunk.h"
#include "PngDef.h"

static const QByteArray PNG_HEADER = QByteArray("\x89PNG\x0D\x0A\x1A\x0A");

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
    , m_ihdrChunk(NULL)
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
    QByteArray header(PNG_HEADER.size(), 0);
    src.readRawData(header.data(), header.size());
    ReturnFailOnFail(PNG_HEADER == header);
    do
    {
        PngChunk *chunk = PngChunk::Create(src);
        ReturnFailOnFail(chunk != NULL);
        m_chunks.append(chunk);
    } while (!src.atEnd());
    ReturnFailOnFail(m_chunks.size() > 0);
    ReturnFailOnFail(m_chunks[0]->GetType() == PngChunk::IHDR);
    m_ihdrChunk = (IHDRChunk *)m_chunks[0];
    return true;
}

void GSPng::Close()
{
    foreach (PngChunk *chunk, m_chunks)
    {
        SafeDelete(chunk);
    }
    m_chunks.clear();
    m_ihdrChunk = NULL;
}

int GSPng::GetSize() const
{
    int size = 0;
    foreach (PngChunk *chunk, m_chunks)
    {
        int chunkSize = chunk->GetSize();
        size += chunkSize;
    }
    return size;
}

int GSPng::GetWidth() const
{
    if (m_ihdrChunk == NULL)
    {
        return 0;
    }
    return m_ihdrChunk->GetWidth();
}

int GSPng::GetHeight() const
{
    if (m_ihdrChunk == NULL)
    {
        return 0;
    }
    return m_ihdrChunk->GetHeight();
}

QImage GSPng::GetImage() const
{
    return QImage();
}

PngChunk * GSPng::GetChunk(enum PngChunk::Type type) const
{
    PngChunk *ret = NULL;
    foreach (PngChunk *chunk, m_chunks)
    {
        if (chunk->GetType() == type)
        {
            ret = chunk;
            break;
        }
    }
    return ret;
}
