#ifndef PNGCHUNK_H
#define PNGCHUNK_H

#include "Core/PngDef.h"

class PngChunk
{
public:
    enum Type
    {
        IHDR = 'IHDR',
        PLTE = 'PLTE',
        IDAT = 'IDAT',
        IEND = 'IEND',
        tRNS = 'tRNS',
        UNSUPPORTED = 0
    };

    static PngChunk * Create(QDataStream &src);

public:
    PngChunk(qint32 type);
    virtual ~PngChunk();

    int GetType() const;
    int GetSize() const;

    bool Read(QDataStream &src, quint32 length);
    bool Write(QDataStream &dst);

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    quint32 GetCRC() const;

protected:
    qint32     m_type;
    QByteArray m_data;
};

#endif // PNGCHUNK_H
