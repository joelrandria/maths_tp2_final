#ifndef FOURIERTRANSFORMBASE_H
#define FOURIERTRANSFORMBASE_H

#include "IFourierTransform.h"

class FourierTransformBase : public IFourierTransform
{
public:

    void transform2D(const ComplexMatrix& signalValues, ComplexMatrix& spectralValues);
    void inverseTransform2D(const ComplexMatrix& spectralValues, ComplexMatrix& signalValues);
};

#endif // FOURIERTRANSFORMBASE_H
