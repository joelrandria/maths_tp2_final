#ifndef FASTFOURIERTRANSFORM_H
#define FASTFOURIERTRANSFORM_H

#include "IFourierTransform.h"

class FastFourierTransform : public IFourierTransform
{
public:

    void transform(const ComplexVector &baseValues, ComplexVector &transformedValues);
    void inverseTransform(const ComplexVector &transformedValues, ComplexVector &baseValues);
};

#endif // FASTFOURIERTRANSFORM_H
