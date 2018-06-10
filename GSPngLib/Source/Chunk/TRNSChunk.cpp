#include "TRNSChunk.h"

TRNSChunk::TRNSChunk()
    : PngChunk(tRNS)
{
}

TRNSChunk::~TRNSChunk()
{
}

quint16 TRNSChunk::GetGrayscale() const
{
    if (m_data.size() != 2)
    {
        GSWarning("Data size of tRNS chunk should be 2");
        return 0;
    }
    QDataStream src(m_data);
    src.setByteOrder(QDataStream::BigEndian);
    quint16 gray = 0;
    src >> gray;
    return gray;
}

void TRNSChunk::SetGrayscale(quint16 gray)
{
    m_data.resize(2);
    QDataStream dst(&m_data, QIODevice::WriteOnly);
    dst.setByteOrder(QDataStream::BigEndian);
    dst << gray;
}

QRgba64 TRNSChunk::GetTruecolor() const
{
    if (m_data.size() != 6)
    {
        GSWarning("Data size of tRNS chunk should be 6");
        return QRgba64();
    }
    QDataStream src(m_data);
    src.setByteOrder(QDataStream::BigEndian);
    quint16 r = 0;
    quint16 g = 0;
    quint16 b = 0;
    src >> r >> g >> b;
    return QRgba64::fromRgba64(r, g, b, 0xFFFF);
}

void TRNSChunk::SetTruecolor(QRgba64 rgb)
{
    m_data.resize(6);
    QDataStream dst(&m_data, QIODevice::WriteOnly);
    dst.setByteOrder(QDataStream::BigEndian);
    dst << rgb.red();
    dst << rgb.green();
    dst << rgb.blue();
}

QVector<quint8> TRNSChunk::GetIndexedAlpha() const
{
    QVector<quint8> alphas(m_data.size(), 0);
    for (int i = 0; i < m_data.size(); ++i)
    {
        alphas[i] = (quint8)m_data[i];
    }
    return alphas;
}

void TRNSChunk::SetIndexedAlpha(const QVector<quint8> &alphas)
{
    m_data.resize(alphas.size());
    for (int i = 0; i < alphas.size(); ++i)
    {
        m_data[i] = (char)alphas[i];
    }
}
