#ifndef TRNSCHUNK_H
#define TRNSCHUNK_H

#include "PngChunk.h"

class TRNSChunk : public PngChunk
{
public:
    TRNSChunk();
    virtual ~TRNSChunk();

public:
    quint16 GetGrayscale();
    void SetGrayscale(quint16 gray);

    QRgba64 GetTruecolor();
    void SetTruecolor(QRgba64 rgb);

    QVector<quint8> GetIndexedAlpha();
    void SetIndexedAlpha(const QVector<quint8> &alphas);
};

#endif // TRNSCHUNK_H
