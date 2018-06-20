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
};

#endif // IDATCHUNK_H
