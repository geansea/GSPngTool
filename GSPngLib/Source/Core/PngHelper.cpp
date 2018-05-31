#include "PngHelper.h"

QByteArray PngHelper::IntToBytesBE(int value)
{
    QByteArray bytes(4, 0);
    bytes[0] = (char)((value >> 24) & 0xFF);
    bytes[1] = (char)((value >> 16) & 0xFF);
    bytes[2] = (char)((value >> 8) & 0xFF);
    bytes[3] = (char)(value & 0xFF);
    return bytes;
}

quint32 PngHelper::UpdateCRC32(quint32 old, const QByteArray &bytes)
{
    return 0;
}
