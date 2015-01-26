#ifndef IFOURIERTRANSFORM_H
#define IFOURIERTRANSFORM_H

#include "Fourier.h"
#include "ComplexMatrix.h"
#include "FourierTransform_Global.h"

class IFourierTransform
{
public:

    virtual ~IFourierTransform(){}

    virtual void transform(const ComplexVector& signalValues, ComplexVector& spectralValues) = 0;
    virtual void transform2D(const ComplexMatrix& signalValues, ComplexMatrix& spectralValues) = 0;

    virtual void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues) = 0;
    virtual void inverseTransform2D(const ComplexMatrix& spectralValues, ComplexMatrix& signalValues) = 0;
};

#endif // IFOURIERTRANSFORM_H
