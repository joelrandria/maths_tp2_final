#ifndef FOURIERLOWPASSFILTER_H
#define FOURIERLOWPASSFILTER_H

#include "IFourierFilter.h"

class FourierLowPassFilter : public IFourierFilter
{
private:

    float m_percentThreshold;

public:

    FourierLowPassFilter();

    void setThreshold(float percentThreshold) { m_percentThreshold = percentThreshold; }

    void filter(ComplexVector& fourierValues);
};

#endif // FOURIERLOWPASSFILTER_H
