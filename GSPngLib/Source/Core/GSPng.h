#ifndef GSPNG_H
#define GSPNG_H

#include "IGSPng.h"
#include "Chunk/PngChunk.h"

class IHDRChunk;
class PLTEChunk;

class GSPng : public IGSPng
{
public:
    GSPng();
    virtual ~GSPng();

    bool Open(QDataStream &src);
    void Close();

public:
    virtual int GetSize() const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual bool IsPaletteBased() const;
    virtual QImage GetImage() const;

private:
    PngChunk * GetChunk(enum PngChunk::Type type) const;

private:
    QList<PngChunk *> m_chunks;
    IHDRChunk * m_ihdrChunk;
    PLTEChunk * m_plteChunk;
};

#endif // GSPNG_H
