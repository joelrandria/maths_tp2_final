#include "FourierLowPassFilter.h"

#include <QDebug>

FourierLowPassFilter::FourierLowPassFilter()
    :m_percentThreshold(-1)
{
}

void FourierLowPassFilter::filter(ComplexVector& fourierValues)
{
    if (m_percentThreshold == 100)
    {
        fourierValues.assign(fourierValues.size(), 0);
        return;
    }

    int halfSize = fourierValues.size() / 2;
    int maxFreqIndex = fourierValues.size() / 2;
    int removeRangeWidth = (int)(m_percentThreshold * (float)halfSize / 100.f);

    qDebug() << QString("%1 frequences à mettre à 0").arg(removeRangeWidth * 2 + 1);

    for (int i = 0; i < removeRangeWidth; ++i)
    {
        fourierValues[maxFreqIndex - i] = 0;
        fourierValues[maxFreqIndex + i] = 0;
    }
}
