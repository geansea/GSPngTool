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
    ReturnFailOnFail(PngChunk::LoadData());
    ReturnFailOnFail(m_data.size() % 3 == 0);
    for (int i = 0; i < m_data.size(); i += 3)
    {
        quint8 r = (quint8)m_data[i];
        quint8 g = (quint8)m_data[i + 1];
        quint8 b = (quint8)m_data[i + 2];
        m_colors.append(QColor(r, g, b));
    }
    return true;
}

bool PLTEChunk::UpdateData()
{
    m_data.resize(m_colors.size() * 3);
    for (int i = 0; i < m_colors.size(); ++i)
    {
        const QColor &color = m_colors[i];
        m_data[i * 3]     = (char)color.red();
        m_data[i * 3 + 1] = (char)color.green();
        m_data[i * 3 + 2] = (char)color.blue();
    }
    ReturnFailOnFail(PngChunk::UpdateData());
    return true;
}
