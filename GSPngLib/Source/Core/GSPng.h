#ifndef GSPNG_H
#define GSPNG_H

#include "IGSPng.h"
#include "Chunk/PngChunk.h"

class IHDRChunk;
class PLTEChunk;
class TRNSChunk;

class GSPng : public IGSPng
{
public:
    GSPng();
    virtual ~GSPng();

    bool Open(QDataStream &src);
    bool Open(const QImage &image);
    void Close();

public:
    virtual int GetSize() const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual QImage GetImage() const;

public:
    virtual bool WriteToFile(const QString &path) const;

private:
    bool InitChunks();
    PngChunk * GetChunk(enum PngChunk::Type type) const;
    bool NeedsPLTChunk() const;
    bool SupportsTRNSChunk() const;

private:
    QList<PngChunk *> m_chunks;
    IHDRChunk * m_ihdrChunk;
    PLTEChunk * m_plteChunk;
    TRNSChunk * m_trnsChunk;
};

#endif // GSPNG_H
