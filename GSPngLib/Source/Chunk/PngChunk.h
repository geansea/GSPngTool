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
    virtual void UpdateData();

private:
    quint32 GetCRC() const;

protected:
    qint32      m_type;
    QByteArray  m_data;
    bool        m_dataChanged;
};

#endif // PNGCHUNK_H
