#include "EdgeFT.h"
#include "FourierTransform.h"

#include <QDebug>

EdgeFT::EdgeFT()
{
}
EdgeFT::EdgeFT(const Edge &edge)
{
    m_fourierCoefficients.resize(edge.constValues().size());

    FourierTransform ft;
    ft.transform(edge.constValues(), m_fourierCoefficients);
}
Edge EdgeFT::edge() const
{
    Edge rebuiltEdge;
    rebuiltEdge.m_values.resize(m_fourierCoefficients.size());

    FourierTransform ft;
    ft.inverseTransform(m_fourierCoefficients, rebuiltEdge.m_values);

    return rebuiltEdge;
}

void EdgeFT::lowPassFilter(float percentThreshold)
{
    if (percentThreshold == 100)
        m_fourierCoefficients.clear();

    int halfSize = m_fourierCoefficients.size() / 2;
    int maxFreqIndex = m_fourierCoefficients.size() / 2;
    int removeRangeWidth = (int)(percentThreshold * (float)halfSize / 100.f);

    qDebug() << QString("%1 frequences à mettre à 0").arg(removeRangeWidth * 2 + 1);

    for (int i = 0; i < removeRangeWidth; ++i)
    {
        m_fourierCoefficients[maxFreqIndex - i] = 0;
        m_fourierCoefficients[maxFreqIndex + i] = 0;
    }
}
