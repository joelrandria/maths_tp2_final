#include "FastFourierTransform.h"

#include <QDebug>

#include <cmath>

void FastFourierTransform::transform(const ComplexVector& signalValues, ComplexVector& spectralValues)
{
    butterflyScaffolding(signalValues, spectralValues, SpectralFourierTransform);
}
void FastFourierTransform::inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues)
{
    butterflyScaffolding(spectralValues, signalValues, SpatialFourierTransform);
}

void FastFourierTransform::butterflyScaffolding(const ComplexVector& baseValues, ComplexVector& compositeValues, FastFourierTransform::FourierTransformType type)
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
            butterfly(*infOrder, signalStart, signalStart + signalsWidth, *supOrder, type);

        swap(infOrder, supOrder);

        signalsWidth *= 2;
    }

    compositeValues = *infOrder;

    if (type == SpectralFourierTransform)
        normalize(compositeValues);

    delete infOrder;
    delete supOrder;
}
void FastFourierTransform::butterfly(const ComplexVector& infOrder, uint start, uint end, ComplexVector& supOrder, FourierTransformType type)
{
    uint m;
    uint M;
    uint half;

    double piFactor;

    M = (end - start) / 2;
    half = (end + start) / 2;

    piFactor = type == SpectralFourierTransform ? -M_PI : M_PI;

    for (m = 0; m < M; ++m)
    {
        supOrder[start + m] = infOrder[start + m] + exp(Complex(0, piFactor * m / M)) * infOrder[half + m];
        supOrder[half + m] = infOrder[start + m] - exp(Complex(0, piFactor * m / M)) * infOrder[half + m];
    }
}

void FastFourierTransform::normalize(ComplexVector& spectralValues)
{
    uint i;
    uint valueCount;

    valueCount = spectralValues.size();

    for (i = 0; i < valueCount; ++i)
        spectralValues[i] = Complex(spectralValues[i].real() / valueCount,
                                       spectralValues[i].imag() / valueCount);
}

void FastFourierTransform::swap(ComplexVector*& vec1, ComplexVector*& vec2)
{
    ComplexVector* temp;

    temp = vec1;
    vec1 = vec2;
    vec2 = temp;
}

void FastFourierTransform::reorder(const ComplexVector& signalValues, ComplexVector& orderedValues)
{
    uint i;
    uint bitcount;
    uint valueCount;

    valueCount = signalValues.size();
    bitcount = (uint)log2(valueCount);

    for (i = 0; i < valueCount; ++i)
        orderedValues[bitReversed(i, bitcount)] = signalValues[i];
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
