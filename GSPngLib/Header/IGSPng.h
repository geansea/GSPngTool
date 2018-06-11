#ifndef IGSPNG_H
#define IGSPNG_H

#include <QtCore>
#include <QtGui>

class IGSPng
{
public:
    virtual ~IGSPng() {}

public:
    virtual int GetSize() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual QImage GetImage() const = 0;

public:
    virtual bool WriteToFile(const QString &path) const = 0;

public:
    static IGSPng * CreateFromFile(const QString &path);
    static IGSPng * CreateFromImage(const QImage &image);
};

#endif // IGSPNG_H
