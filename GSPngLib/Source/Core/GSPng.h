#ifndef GSPNG_H
#define GSPNG_H

#include "IGSPng.h"
#include "Chunk/PngChunk.h"

class IHDRChunk;
class PLTEChunk;
class IDATChunk;
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
    virtual QString GetMetadata() const;
    virtual QImage GetImage() const;

public:
    virtual void DoQuickOptimize();
    virtual void DoLosslessOptimize();
    virtual void DoLossyOptimize();
    virtual bool WriteToFile(const QString &path) const;

private:
    bool InitChunks();
    bool NeedsPLTChunk() const;
    bool SupportsTRNSChunk() const;

    // Lossless optimization
    void RemoveUnnecessaryChunks();
    void ChooseBetterColorMode();
    void ChooseBetterFilterMode();

    // Lossy optimization
    void ReduceColors();

private:
    QList<PngChunk *>  m_chunks;
    IHDRChunk *        m_ihdrChunk;
    PLTEChunk *        m_plteChunk;
    QList<IDATChunk *> m_dataChunks;
    TRNSChunk *        m_trnsChunk;
};

#endif // GSPNG_H
