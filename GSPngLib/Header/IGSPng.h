#ifndef IGSPNG_H
#define IGSPNG_H

#include "GSPngDef.h"

class IGSPng
{
public:
    virtual ~IGSPng() {}

public:
    struct Chunk
    {
        qint32 length;
        qint32 type;
        QByteArray data;
        quint32 crc;

        Chunk();
        bool Read(QDataStream &src);
        bool Write(QDataStream &dst);
    };

};

#endif // IGSPNG_H
