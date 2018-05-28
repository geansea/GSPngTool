#include "IHDRChunk.h"

IHDRChunk::IHDRChunk()
    : PngChunk(IHDR)
{

}

IHDRChunk::~IHDRChunk()
{

}

bool IHDRChunk::Read(QDataStream &src, quint32 length)
{
    return false;
}

QByteArray IHDRChunk::GetData() const
{
    return QByteArray();
}
