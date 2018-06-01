#include "GSPng.h"
#include "Chunk/IHDRChunk.h"
#include "Chunk/PLTEChunk.h"
#include "PngDef.h"

static const QByteArray PNG_HEADER = QByteArray("\x89PNG\x0D\x0A\x1A\x0A");

IGSPng * IGSPng::CreateFromFile(const QString &path)
{
    QFile file(path);
    ReturnNullOnFail(file.open(QIODevice::ReadOnly));
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    GSPng *png = new GSPng();
    GSPointerScope<GSPng> scope(png);
    ReturnNullOnFail(png->Open(stream));
    scope.Cancel();
    return png;
}

GSPng::GSPng()
    : m_chunks()
    , m_ihdrChunk(NULL)
    , m_plteChunk(NULL)
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
    ReturnFailOnFail(src.readRawData(header.data(), header.size()) == header.size());
    ReturnFailOnFail(PNG_HEADER == header);
    do
    {
        PngChunk *chunk = PngChunk::Create(src);
        ReturnFailOnFail(chunk != NULL);
        m_chunks.append(chunk);
    } while (!src.atEnd());
    ReturnFailOnFail(m_chunks.size() > 0);
    ReturnFailOnFail(m_chunks.first()->GetType() == PngChunk::IHDR);
    ReturnFailOnFail(m_chunks.last()->GetType() == PngChunk::IEND);

    m_ihdrChunk = (IHDRChunk *)m_chunks.first();
    if (IsPaletteBased())
    {
        m_plteChunk = (PLTEChunk *)GetChunk(PngChunk::PLTE);
    }
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
    int size = PNG_HEADER.size();
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

bool GSPng::IsPaletteBased() const
{
    if (m_ihdrChunk == NULL)
    {
        return false;
    }
    return m_ihdrChunk->GetColorType() == PngIndexedColor;
}

QImage GSPng::GetImage() const
{
    return QImage();
}

bool GSPng::WriteToFile(const QString &path) const
{
    QFile file(path);
    ReturnFailOnFail(file.open(QIODevice::WriteOnly));
    QDataStream dst(&file);
    dst.setByteOrder(QDataStream::BigEndian);

    ReturnFailOnFail(dst.writeRawData(PNG_HEADER.data(), PNG_HEADER.size()) == PNG_HEADER.size());
    foreach (PngChunk *chunk, m_chunks)
    {
        ReturnFailOnFail(chunk->Write(dst));
    }
    return true;
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
