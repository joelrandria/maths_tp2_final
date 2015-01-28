#ifndef IFOURIERFILTER_H
#define IFOURIERFILTER_H

#include "Fourier.h"
#include "ComplexMatrix.h"

class IFourierFilter
{
public:

    virtual ~IFourierFilter(){}

    virtual void filter(ComplexVector& spectrum) = 0;
    virtual void filter2D(ComplexMatrix& spectrum) = 0;
};

#endif // IFOURIERFILTER_H
