#ifndef IPNGCHUNK_H
#define IPNGCHUNK_H

#include "Core/PngDef.h"

class IPngChunk
{
public:
    enum Type
    {
        IHDR = 'IHDR',
        UNSUPPORTED = 0
    };

    static IPngChunk * Create(QDataStream &src);

public:
    virtual ~IPngChunk() {}

    virtual Type Type() const = 0;
    virtual int TypeValue() const = 0;
    virtual int Size() const = 0;
    virtual bool Write(QDataStream &dst) const = 0;
};

#endif // IPNGCHUNK_H
