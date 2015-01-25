#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "IFourierTransform.h"

class FourierTransform : public IFourierTransform
{
public:

    void transform(const ComplexVector& signalValues, ComplexVector& spectralValues);
    void transform(const ComplexMatrix& signalValues, ComplexMatrix& spectralValues);

    void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues);
    void inverseTransform(const ComplexMatrix& spectralValues, ComplexMatrix& signalValues);
};

#endif // FOURIERTRANSFORM_H
