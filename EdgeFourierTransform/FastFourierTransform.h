#ifndef FASTFOURIERTRANSFORM_H
#define FASTFOURIERTRANSFORM_H

#include "IFourierTransform.h"

#include <QString>

class FastFourierTransform : public IFourierTransform
{
public:

    void transform(const ComplexVector& baseValues, ComplexVector& transformedValues);
    void inverseTransform(const ComplexVector& transformedValues, ComplexVector& baseValues);

    static void printValues(const QString& title, const ComplexVector& values);

private:

    void reorder(const ComplexVector& baseValues, ComplexVector& orderedValues);
    uint bitReversed(uint value, uint bitCount);

    void butterfly(const ComplexVector& infOrder, uint start, uint end, ComplexVector& supOrder);

    void normalize(ComplexVector& transformedValues);
    void swap(ComplexVector*& vec1, ComplexVector*& vec2);
};

#endif // FASTFOURIERTRANSFORM_H
