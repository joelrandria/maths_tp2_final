#ifndef FOURIERPASSFILTERBASE_H
#define FOURIERPASSFILTERBASE_H

#include "IFourierFilter.h"

class FourierPassFilterBase : public IFourierFilter
{
private:

    float m_percentThreshold;

public:

    void setThreshold(float percentThreshold) { m_percentThreshold = percentThreshold; }

    void filter(ComplexVector& spectrum);
    void filter2D(ComplexMatrix& spectrum);

private:

    float distance(float r1, float c1, float r2, float c2) const;
    float spectrumHalfDiagonalLength(ComplexMatrix &spectrum) const;

protected:

    virtual bool accept(float pointDistance, float thresholdDistance) = 0;
};

#endif // FOURIERPASSFILTERBASE_H
