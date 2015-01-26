#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "FourierTransformBase.h"

class FourierTransform : public FourierTransformBase
{
public:

    void transform(const ComplexVector& signalValues, ComplexVector& spectralValues);
    void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues);
};

#endif // FOURIERTRANSFORM_H
