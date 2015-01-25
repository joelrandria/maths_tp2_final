#ifndef FASTFOURIERTRANSFORM_H
#define FASTFOURIERTRANSFORM_H

#include "IFourierTransform.h"

#include <QString>

class FastFourierTransform : public IFourierTransform
{
private:

    enum FourierTransformType
    {
        SpatialFourierTransform,
        SpectralFourierTransform
    };

public:

    void transform(const ComplexVector& signalValues, ComplexVector& spectralValues);
    void inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues);

private:

    void reorder(const ComplexVector& signalValues, ComplexVector& orderedValues);
    uint bitReversed(uint value, uint bitCount);

    void butterflyScaffolding(const ComplexVector& baseValues, ComplexVector& compositeValues, FourierTransformType type);
    void butterfly(const ComplexVector& infOrder, uint start, uint end, ComplexVector& supOrder, FourierTransformType type);

    void normalize(ComplexVector& spectralValues);
    void swap(ComplexVector*& vec1, ComplexVector*& vec2);
};

#endif // FASTFOURIERTRANSFORM_H