#ifndef FOURIERHIGHPASSFILTER_H
#define FOURIERHIGHPASSFILTER_H

#include "FourierPassFilterBase.h"

class FourierHighPassFilter : public FourierPassFilterBase
{
protected:

    bool accept(float pointDistance, float thresholdDistance);
};

#endif // FOURIERHIGHPASSFILTER_H
