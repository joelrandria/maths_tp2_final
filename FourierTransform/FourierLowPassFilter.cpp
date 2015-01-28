#include "FourierLowPassFilter.h"

bool FourierLowPassFilter::accept(float pointDistance, float thresholdDistance)
{
    return pointDistance < thresholdDistance;
}
