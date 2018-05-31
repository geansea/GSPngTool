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
    virtual bool LoadData();
    virtual void UpdateData();

private:
    QByteArray m_imageData;
};

#endif // IDATCHUNK_H
