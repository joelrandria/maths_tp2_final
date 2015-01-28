#ifndef FOURIERLOWPASSFILTER_H
#define FOURIERLOWPASSFILTER_H

#include "FourierPassFilterBase.h"

class FourierLowPassFilter : public FourierPassFilterBase
{
protected:

    bool accept(float pointDistance, float thresholdDistance);
};

#endif // FOURIERLOWPASSFILTER_H
