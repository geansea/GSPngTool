#ifndef PNGCHUNK_H
#define PNGCHUNK_H

#include <QtCore>

class PngChunk
{
public:
    enum Type
    {
        IHDR = 'IHDR',
        UNSUPPORTED = 0
    };

    static PngChunk * Create(QDataStream &src);

protected:
    static QByteArray IntToBytesBE(int value);

public:
    PngChunk(qint32 type);
    virtual ~PngChunk();

    int Type() const;
    int Size() const;
    bool Write(QDataStream &dst) const;

protected:
    virtual bool Read(QDataStream &src, quint32 length);
    virtual QByteArray GetData() const;

private:
    quint32 GetCRC() const;

protected:
    qint32      m_type;
    QByteArray  m_data;
};

#endif // PNGCHUNK_H
