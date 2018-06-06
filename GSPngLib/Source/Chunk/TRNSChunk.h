#ifndef TRNSCHUNK_H
#define TRNSCHUNK_H

#include "PngChunk.h"

class TRNSChunk : public PngChunk
{
public:
    TRNSChunk();
    virtual ~TRNSChunk();

public:
    quint16 GetGrayscale() const;
    void SetGrayscale(quint16 gray);

    QRgba64 GetTruecolor() const;
    void SetTruecolor(QRgba64 rgb);

    QVector<quint8> GetIndexedAlpha() const;
    void SetIndexedAlpha(const QVector<quint8> &alphas);
};

#endif // TRNSCHUNK_H
