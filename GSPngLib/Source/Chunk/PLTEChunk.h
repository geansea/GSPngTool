#ifndef PLTECHUNK_H
#define PLTECHUNK_H

#include "PngChunk.h"

class PLTEChunk : public PngChunk
{
public:
    PLTEChunk();
    virtual ~PLTEChunk();

public:
    const QVector<QRgb> & GetColors() const;

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    QVector<QRgb> m_colors;
};

#endif // PLTECHUNK_H
