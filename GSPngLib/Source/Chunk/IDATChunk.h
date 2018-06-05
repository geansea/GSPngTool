#ifndef IDATCHUNK_H
#define IDATCHUNK_H

#include "PngChunk.h"

class IDATChunk : public PngChunk
{
public:
    IDATChunk();
    virtual ~IDATChunk();

public:
    QByteArray GetImageData() const;
    void SetImageData(const QByteArray &imageData);

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    QByteArray m_imageData;
};

#endif // IDATCHUNK_H
