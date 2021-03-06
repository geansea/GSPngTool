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
    virtual QString GetMetadata() const = 0;
    virtual QImage GetImage() const = 0;

public:
    virtual void DoQuickOptimize() = 0;
    virtual void DoLosslessOptimize() = 0;
    virtual void DoLossyOptimize() = 0;
    virtual bool WriteToFile(const QString &path) const = 0;

public:
    static IGSPng * CreateFromFile(const QString &path);
    static IGSPng * CreateFromImage(const QImage &image);
};

#endif // IGSPNG_H
