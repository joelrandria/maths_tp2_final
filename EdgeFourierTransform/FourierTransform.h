#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "IFourierTransform.h"

class FourierTransform : public IFourierTransform
{
public:

    void transform(const ComplexVector& signalValues, ComplexVector& spectralValues);
    void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues);
};

#endif // FOURIERTRANSFORM_H
