#include "FourierHighPassFilter.h"

bool FourierHighPassFilter::accept(float pointDistance, float thresholdDistance)
{
    return pointDistance > thresholdDistance;
}
