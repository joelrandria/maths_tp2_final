#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include "Fourier.h"

class IFourierTransform
{
public:

    void transform(const ComplexVector& baseValues, ComplexVector& transformedValues);
    void inverseTransform(const ComplexVector& transformedValues, ComplexVector& baseValues);
};

#endif // IFOURIERTRANSFORM_H
