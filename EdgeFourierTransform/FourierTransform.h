#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "IFourierTransform.h"

class FourierTransform : public IFourierTransform
{
public:

    void transform(const ComplexVector& baseValues, ComplexVector& transformedValues);
    void inverseTransform(const ComplexVector& transformedValues, ComplexVector& baseValues);
};

#endif // FOURIERTRANSFORM_H
