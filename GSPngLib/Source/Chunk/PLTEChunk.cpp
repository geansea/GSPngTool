#include "PLTEChunk.h"

PLTEChunk::PLTEChunk()
    : PngChunk(PLTE)
    , m_colors()
{
}

PLTEChunk::~PLTEChunk()
{
}

const QVector<QColor> & PLTEChunk::GetColors() const
{
    return m_colors;
}

bool PLTEChunk::LoadData()
{
    PngChunk::LoadData();
    ReturnFailOnFail(m_data.size() % 3 == 0);
    QDataStream src(&m_data, QIODevice::ReadOnly);
    quint32 r = 0, g = 0, b = 0;
    for (quint32 i = 0; i < m_data.size() / 3; ++i)
    {
        src >> r >> g >> b;
        QColor color(r, g, b);
        m_colors.append(color);
    }
    ReturnFailOnFail(src.status() == QDataStream::Status::Ok);
    ReturnFailOnFail(src.atEnd());
    return true;
}

void PLTEChunk::UpdateData()
{
    m_data.resize(m_colors.size() * 3);
    QDataStream dst(&m_data, QIODevice::WriteOnly);
    quint32 r = 0, g = 0, b = 0;
    for (int i = 0; i < m_colors.size(); ++i)
    {
        const QColor &color = m_colors[i];
        r = (quint32)color.red();
        g = (quint32)color.green();
        b = (quint32)color.blue();
        dst << r << g << b;
    }
    PngChunk::UpdateData();
}
