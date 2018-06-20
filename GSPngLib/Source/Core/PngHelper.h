#ifndef PNGHELPER_H
#define PNGHELPER_H

#include "PngDef.h"

class PngHelper
{
public:
    static QByteArray IntToBytesBE(int value);
    static QString IntToString(int value);
    static quint32 UpdateCRC32(quint32 old, const QByteArray &bytes);

private:
    PngHelper();
};

#endif // PNGHELPER_H
