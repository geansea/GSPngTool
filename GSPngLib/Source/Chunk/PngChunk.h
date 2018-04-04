#ifndef PNGCHUNK_H
#define PNGCHUNK_H

#include <QtCore>

class PngChunk
{

public:
    PngChunk(quint32 length, qint32 type);
    virtual ~PngChunk();

    virtual Type Type() const;
    virtual int TypeValue() const;
    virtual int Size() const;
    virtual bool Write(QDataStream &dst) const;

public:
    static quint32 Crc(qint32 type, const QByteArray &data);
    static bool Write(qint32 type, const QByteArray &data, QDataStream &dst);

protected:
    qint32      m_type;
    QByteArray  m_data;
    quint32     m_crc;
};

#endif // PNGCHUNK_H
