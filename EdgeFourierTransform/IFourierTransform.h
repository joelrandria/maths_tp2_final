#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include "Fourier.h"

class IFourierTransform
{
public:

    virtual void transform(const ComplexVector& baseValues, ComplexVector& transformedValues) = 0;
    virtual void inverseTransform(const ComplexVector& transformedValues, ComplexVector& baseValues) = 0;
};

#endif // IFOURIERTRANSFORM_H
