#ifndef PLTECHUNK_H
#define PLTECHUNK_H

#include "PngChunk.h"
#include <QColor>

class PLTEChunk : public PngChunk
{
public:
    PLTEChunk();
    virtual ~PLTEChunk();

public:
    const QVector<QColor> & GetColors() const;

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    QVector<QColor> m_colors;
};

#endif // PLTECHUNK_H
