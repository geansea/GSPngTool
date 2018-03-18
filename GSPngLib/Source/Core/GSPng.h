#ifndef GSPNG_H
#define GSPNG_H

#include "IGSPng.h"

class GSPng : public IGSPng
{
public:
    GSPng();
    virtual ~GSPng();

    bool Open(QDataStream &src);
    void Close();

public:
    virtual int Size() const;
    virtual int Width() const;
    virtual int Height() const;
    virtual QImage Image() const;
};

#endif // GSPNG_H
