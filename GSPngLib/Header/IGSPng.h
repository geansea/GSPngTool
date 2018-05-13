#ifndef IGSPNG_H
#define IGSPNG_H

#include <QtCore>
#include <QtGui>

class IGSPng
{
public:
    virtual ~IGSPng() {}

public:
    virtual int Size() const = 0;
    virtual int Width() const = 0;
    virtual int Height() const = 0;
    virtual QImage Image() const = 0;

public:
    static IGSPng * CreateFromFile(const QString &path);
    //static IGSPng * CreateFromImage(const QImage &image);
};

#endif // IGSPNG_H
