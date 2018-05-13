#ifndef GSPNG_H
#define GSPNG_H

#include "IGSPng.h"
#include "Chunk/PngChunk.h"

class GSPng : public IGSPng
{
public:
    GSPng();
    virtual ~GSPng();

    bool Open(QDataStream &src);
    void Close();

public:
    virtual int Size() const;
    virtual int Width() const;
    virtual int Height() const;
    virtual QImage Image() const;

private:
    PngChunk * GetChunk(enum PngChunk::Type type) const;

private:
    QList<PngChunk *> m_chunks;
};

#endif // GSPNG_H
