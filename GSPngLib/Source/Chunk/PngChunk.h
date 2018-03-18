#ifndef PNGCHUNK_H
#define PNGCHUNK_H

#include <QtCore>

class PngChunk
{
public:
    enum Type
    {
        IHDR = 'IHDR',
        UNKNOWN = 0
    };

    static PngChunk * Create(QDataStream &src);

public:
    PngChunk(quint32 length, qint32 type);
    virtual ~PngChunk();

    int Type() const;

protected:
    virtual bool Read(QDataStream &src);
    virtual bool IsValid() const;
    quint32 ValidCRC() const;

public:
    int Size() const;
    bool Write(QDataStream &dst);

protected:
    quint32 m_length;
    qint32 m_type;
    QByteArray m_data;
    quint32 m_crc;
};

#endif // PNGCHUNK_H
