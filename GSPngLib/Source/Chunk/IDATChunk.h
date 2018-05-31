#ifndef IDATCHUNK_H
#define IDATCHUNK_H

#include "PngChunk.h"

class IDATChunk : public PngChunk
{
public:
    IDATChunk();
    virtual ~IDATChunk();

public:
    const QByteArray & GetImageData() const;

protected:
    virtual bool Read(QDataStream &src, quint32 length);
    virtual QByteArray GetData() const;

private:
    QByteArray m_imageData;
};

#endif // IDATCHUNK_H
