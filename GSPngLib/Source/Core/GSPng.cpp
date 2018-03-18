#include "GSPng.h"

IGSPng * IGSPng::CreateFromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return NULL;
    }
    GSPng *png = new GSPng();
    if (png != NULL)
    {
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::BigEndian);
        png->Open(stream);
    }
    file.close();
    return png;
}

IGSPng * IGSPng::CreateFromImage(const QImage &image)
{
    return NULL;
}

GSPng::GSPng()
{
}

GSPng::~GSPng()
{
}
