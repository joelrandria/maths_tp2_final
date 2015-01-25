#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include "Fourier.h"

class IFourierTransform
{
public:

    virtual void transform(const ComplexVector& signalValues, ComplexVector& spectralValues) = 0;
    virtual void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues) = 0;
};

#endif // IFOURIERTRANSFORM_H
