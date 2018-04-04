#include "PngChunk_IHDR.h"
#include "Core/PngDef.h"

PngChunk_IHDR::PngChunk_IHDR(quint32 length, qint32 type)
    : PngChunk(length, type)
{
}

PngChunk_IHDR::~PngChunk_IHDR()
{
}

bool PngChunk_IHDR::Read(QDataStream &src)
{
    CheckForReturnFail(PngChunk::Read(src));
    QDataStream dataStream(m_data);
    return true;
}

bool PngChunk_IHDR::IsValid() const
{
    CheckForReturnFail(PngChunk::IsValid());
    return true;
}
