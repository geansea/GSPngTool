#include "PngHelper.h"

QByteArray PngHelper::IntToBytesBE(int value)
{
    QByteArray bytes(4, 0);
    QDataStream dst(&bytes, QIODevice::WriteOnly);
    dst.setByteOrder(QDataStream::BigEndian);
    dst << (qint32)value;
    return bytes;
}

QString PngHelper::IntToString(int value)
{
    return QString::fromLatin1(IntToBytesBE(value));
}

quint32 PngHelper::UpdateCRC32(quint32 old, const QByteArray &bytes)
{
    static QVector<quint32> CRC_TABLE;
    if (CRC_TABLE.size() == 0)
    {
        CRC_TABLE.resize(256);
        for (int i = 0; i < 256; ++i)
        {
            quint32 crc = i;
            for (int j = 0; j < 8; ++j)
            {
                crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
            }
            CRC_TABLE[i] = crc;
        }
    }
    quint32 crc = old ^ 0xFFFFFFFF;
    for (int i = 0; i < bytes.size(); ++i)
    {
        crc = CRC_TABLE[(crc ^ bytes[i]) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFF;
}
