#ifndef IFOURIERFILTER_H
#define IFOURIERFILTER_H

#include "Fourier.h"

class IFourierFilter
{
public:

    virtual void filter(ComplexVector& fourierValues) = 0;
};

#endif // IFOURIERFILTER_H
