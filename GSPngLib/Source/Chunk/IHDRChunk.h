#ifndef IHDRCHUNK_H
#define IHDRCHUNK_H

#include "PngChunk.h"

class IHDRChunk : public PngChunk
{
public:
    IHDRChunk();
    virtual ~IHDRChunk();

public:

protected:
    virtual bool Read(QDataStream &src, quint32 length);
    virtual QByteArray GetData() const;
};

#endif // IHDRCHUNK_H
