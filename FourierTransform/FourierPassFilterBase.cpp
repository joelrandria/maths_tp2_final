#include "FourierPassFilterBase.h"

#include <cmath>
#include <stdexcept>

void FourierPassFilterBase::filter(ComplexVector& spectrum)
{
    if (m_percentThreshold == 100)
    {
        spectrum.assign(spectrum.size(), 0);
        return;
    }

    int halfSize = spectrum.size() / 2;
    int maxFreqIndex = spectrum.size() / 2;
    int removeRangeWidth = (int)(m_percentThreshold * (float)halfSize / 100.f);

    for (int i = 0; i < removeRangeWidth; ++i)
    {
        spectrum[maxFreqIndex - i] = 0;
        spectrum[maxFreqIndex + i] = 0;
    }
}
void FourierPassFilterBase::filter2D(ComplexMatrix &spectrum)
{
    int r;
    int c;
    int rowCount;
    int colCount;

    float centerRow;
    float centerCol;
    float thresholdDistance;

    if (spectrum.isEmpty())
        return;
    if (spectrum.alignment() != ComplexMatrix::HighFrequencyMajorAlignment)
        throw std::invalid_argument("FourierLowPassFilter::filter2D(): Le spectre spécifié doit être centré sur les basses fréquences");

    rowCount = spectrum.rows();
    colCount = spectrum.cols();

    centerRow = (float)spectrum.rows() / 2;
    centerCol = (float)spectrum.cols() / 2;

    thresholdDistance = m_percentThreshold * spectrumHalfDiagonalLength(spectrum) / 100;

    for (r = 0; r < rowCount; ++r)
        for (c = 0; c < colCount; ++c)
            if (!accept(distance(r, c, centerRow, centerCol), thresholdDistance))
                spectrum.at(r, c) = Complex(0, 0);
}

float FourierPassFilterBase::distance(float r1, float c1, float r2, float c2) const
{
    return sqrt(pow((r2 - r1), 2) + pow((c2 - c1), 2));
}
float FourierPassFilterBase::spectrumHalfDiagonalLength(ComplexMatrix &spectrum) const
{
    float hw;
    float hh;

    hw = (float)spectrum.cols() / 2;
    hh = (float)spectrum.rows() / 2;

    return hypot(hw, hh);
}
