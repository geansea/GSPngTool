#include "GSPng.h"
#include "Chunk/IHDRChunk.h"
#include "Chunk/PLTEChunk.h"
#include "Chunk/IDATChunk.h"
#include "Chunk/TRNSChunk.h"
#include "PngHelper.h"

static const QByteArray PNG_HEADER = QByteArray("\x89PNG\x0D\x0A\x1A\x0A");

IGSPng * IGSPng::CreateFromFile(const QString &path)
{
    QFile file(path);
    GSRNF(file.open(QIODevice::ReadOnly));
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    GSPng *png = new GSPng();
    GSPointerScope<GSPng> scope(png);
    GSRNF(png->Open(stream));
    scope.Cancel();
    return png;
}

IGSPng * IGSPng::CreateFromImage(const QImage &image)
{
    GSPng *png = new GSPng();
    GSPointerScope<GSPng> scope(png);
    GSRNF(png->Open(image));
    scope.Cancel();
    return png;
}

GSPng::GSPng()
    : m_chunks()
    , m_ihdrChunk(NULL)
    , m_plteChunk(NULL)
    , m_dataChunks()
    , m_trnsChunk(NULL)
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
    GSRFF(src.readRawData(header.data(), header.size()) == header.size());
    GSRFF(PNG_HEADER == header);
    do
    {
        PngChunk *chunk = PngChunk::Create(src);
        GSRFF(chunk != NULL);
        m_chunks.append(chunk);
    } while (!src.atEnd());
    GSRFF(InitChunks());
    return true;
}

bool GSPng::Open(const QImage &image)
{
    Q_UNUSED(image);
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
    m_plteChunk = NULL;
    m_dataChunks.clear();
    m_trnsChunk = NULL;
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

QString GSPng::GetMetadata() const
{
    QString meta;
    return meta;
}

QImage GSPng::GetImage() const
{
    int width = GetWidth();
    int height = GetHeight();
    QImage::Format format = QImage::Format_ARGB32;
    QImage image(width, height, format);
    return image;
}

void GSPng::DoLosslessOptimize()
{
    RemoveUnnecessaryChunks();
    ChooseBetterColorMode();
    ChooseBetterFilterMode();
}

void GSPng::DoLossyOptimize()
{
    RemoveUnnecessaryChunks();
    ReduceColors();
    ChooseBetterColorMode();
    ChooseBetterFilterMode();
}

bool GSPng::WriteToFile(const QString &path) const
{
    QFile file(path);
    GSRFF(file.open(QIODevice::WriteOnly));
    QDataStream dst(&file);
    dst.setByteOrder(QDataStream::BigEndian);

    GSRFF(dst.writeRawData(PNG_HEADER.data(), PNG_HEADER.size()) == PNG_HEADER.size());
    foreach (PngChunk *chunk, m_chunks)
    {
        GSRFF(chunk->Write(dst));
    }
    return true;
}

bool GSPng::InitChunks()
{
    // Check chunks order
    GSRFF(m_chunks.size() > 0);
    GSRFFL(m_chunks.first()->GetType() == PngChunk::IHDR, "IHDR should be the first chunk");
    GSRFFL(m_chunks.last()->GetType() == PngChunk::IEND, "IEND should be the last chunk");

    QSet<PngChunk::Type> appearedChunks;
    int idatStartIndex = 0;
    int idatEndIndex = 0;
    int index = 0;
    foreach (PngChunk *chunk, m_chunks)
    {
        PngChunk::Type type = chunk->GetType();
        if (appearedChunks.contains(type))
        {
            GSRFFL(PngChunk::AllowsMultiple(type), QString(PngHelper::IntToBytesBE(type)) + " is not Multiple allowed");
        }
        else
        {
            appearedChunks.insert(type);
        }

        switch (type)
        {
        case PngChunk::IHDR:
            m_ihdrChunk = (IHDRChunk *) chunk;
            break;
        case PngChunk::PLTE:
            m_plteChunk = (PLTEChunk *) chunk;
            break;
        case PngChunk::IDAT:
            if (idatStartIndex == 0)
            {
                idatStartIndex = index;
            }
            else
            {
                GSRFFL(idatEndIndex == index, "IDAT chunks should be consecutive");
            }
            idatEndIndex = index + 1;
            break;
        case PngChunk::tRNS:
            GSRFFL(idatStartIndex == 0, "tRNS chunk should before IDAT chunk");
            m_trnsChunk = (TRNSChunk *) chunk;
            break;
        default:
            break;
        }
        ++index;
    }
    return true;
}

bool GSPng::NeedsPLTChunk() const
{
    GSRFF(m_ihdrChunk != NULL);
    return m_ihdrChunk->GetColorType() == PngIndexedColor;
}

bool GSPng::SupportsTRNSChunk() const
{
    GSRFF(m_ihdrChunk != NULL);
    switch (m_ihdrChunk->GetColorType())
    {
    case PngGrayscale:
    case PngTruecolor:
    case PngIndexedColor:
        return true;
    default:
        return false;
    }
}

void GSPng::RemoveUnnecessaryChunks()
{
}

void GSPng::ChooseBetterColorMode()
{
}

void GSPng::ChooseBetterFilterMode()
{
}

void GSPng::ReduceColors()
{
}
