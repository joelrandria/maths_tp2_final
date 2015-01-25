#include "FastFourierTransform.h"

#include <QDebug>

#include <cmath>

void FastFourierTransform::transform(const ComplexVector& baseValues, ComplexVector& transformedValues)
{
    uint signalStart;
    uint signalsWidth;
    uint valueCount;

    ComplexVector* infOrder;
    ComplexVector* supOrder;

    valueCount = baseValues.size();

    infOrder = new ComplexVector(valueCount);
    reorder(baseValues, *infOrder);

    supOrder = new ComplexVector(valueCount);
    *supOrder = baseValues;

    signalsWidth = 2;

    while (signalsWidth <= valueCount)
    {
        for (signalStart = 0; signalStart < valueCount; signalStart += signalsWidth)
            butterfly(*infOrder, signalStart, signalStart + signalsWidth, *supOrder);

        swap(infOrder, supOrder);

        signalsWidth *= 2;
    }

    transformedValues = *infOrder;

    normalize(transformedValues);

    delete infOrder;
    delete supOrder;
}
void FastFourierTransform::butterfly(const ComplexVector& infOrder, uint start, uint end, ComplexVector& supOrder)
{
    uint m;
    uint M;
    uint half;

    M = (end - start) / 2;
    half = (end + start) / 2;

    for (m = 0; m < M; ++m)
    {
        supOrder[start + m] = infOrder[start + m] + exp(Complex(0, -M_PI * m / M)) * infOrder[half + m];
        supOrder[half + m] = infOrder[start + m] - exp(Complex(0, -M_PI * m / M)) * infOrder[half + m];
    }
}

void FastFourierTransform::normalize(ComplexVector &transformedValues)
{
    uint i;
    uint valueCount;

    valueCount = transformedValues.size();

    for (i = 0; i < valueCount; ++i)
        transformedValues[i] = Complex(transformedValues[i].real() / valueCount,
                                       transformedValues[i].imag() / valueCount);
}

void FastFourierTransform::swap(ComplexVector*& vec1, ComplexVector*& vec2)
{
    ComplexVector* temp;

    temp = vec1;
    vec1 = vec2;
    vec2 = temp;
}

void FastFourierTransform::inverseTransform(const ComplexVector& transformedValues, ComplexVector& baseValues)
{
}

void FastFourierTransform::printValues(const QString& title, const ComplexVector& values)
{
    uint i;

    qDebug() << title;

    for (i = 0; i < values.size(); ++i)
        qDebug() << QString("<%1,%2> ")
                    .arg(values[i].real())
                    .arg(values[i].imag());
}

void FastFourierTransform::reorder(const ComplexVector& baseValues, ComplexVector& orderedValues)
{
    uint i;
    uint bitcount;
    uint valueCount;

    valueCount = baseValues.size();
    bitcount = (uint)log2(valueCount);

    for (i = 0; i < valueCount; ++i)
        orderedValues[bitReversed(i, bitcount)] = baseValues[i];
}
uint FastFourierTransform::bitReversed(uint value, uint bitCount)
{
    uint i;
    uint reversed;
    uint index;

    reversed = 0;
    index = bitCount - 1;

    for (i = 0; i < bitCount; ++i)
    {
        if (value&  (1 << i))
            reversed |= 1 << index;

        --index;
    }

    return reversed;
}
