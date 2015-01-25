#include "FastFourierTransform.h"

#include <cmath>
#include <stdexcept>

void FastFourierTransform::transform(const ComplexVector& signalValues, ComplexVector& spectralValues)
{
    if (signalValues.size() != spectralValues.size())
        throw new std::invalid_argument("FastFourierTransform::transform(): Les vecteurs d'entrée et de sortie doivent être de mêmes tailles");
    if (!isPow2((double)signalValues.size()))
        throw new std::invalid_argument("FastFourierTransform::transform(): La taille du signal doit être une puissance de 2");

    butterflyScaffolding(signalValues, spectralValues, SpectralFourierTransform);
}
void FastFourierTransform::transform(const ComplexMatrix &signalValues, ComplexMatrix &spectralValues)
{
    int r;
    int rowCount;

    ComplexMatrix workingMatrix;

    // Transformée des lignes
    workingMatrix.resize(signalValues.rows(), signalValues.cols());

    rowCount = workingMatrix.rows();

    for (r = 0; r < rowCount; ++r)
        transform(signalValues.at(r), workingMatrix.at(r));

    // Transformée des colonnes
    workingMatrix.transpose();
    spectralValues.resize(workingMatrix.rows(), workingMatrix.cols());

    rowCount = workingMatrix.rows();

    for (r = 0; r < rowCount; ++r)
        transform(workingMatrix.at(r), spectralValues.at(r));

    // Transposition finale
    spectralValues.transpose();
}
void FastFourierTransform::inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues)
{
    if (signalValues.size() != spectralValues.size())
        throw new std::invalid_argument("FastFourierTransform::transform(): Les vecteurs d'entrée et de sortie doivent être de mêmes tailles");
    if (!isPow2((double)spectralValues.size()))
        throw new std::invalid_argument("FastFourierTransform::transform(): La taille du signal doit être une puissance de 2");

    butterflyScaffolding(spectralValues, signalValues, SpatialFourierTransform);
}
void FastFourierTransform::inverseTransform(const ComplexMatrix &spectralValues, ComplexMatrix &signalValues)
{
    int r;
    int rowCount;

    ComplexMatrix spectralCopy;
    ComplexMatrix workingMatrix;

    spectralCopy = spectralValues;
    spectralCopy.transpose();

    // Transformée des colonnes
    workingMatrix.resize(spectralCopy.rows(), spectralCopy.cols());

    rowCount = spectralCopy.rows();

    for (r = 0; r < rowCount; ++r)
        inverseTransform(spectralCopy.at(r), workingMatrix.at(r));

    // Transformée des lignes
    workingMatrix.transpose();
    signalValues.resize(workingMatrix.rows(), workingMatrix.cols());

    rowCount = workingMatrix.rows();

    for (r = 0; r < rowCount; ++r)
        inverseTransform(workingMatrix.at(r), signalValues.at(r));
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

bool FastFourierTransform::isPow2(double value)
{
    return value == pow(2, log2(value));
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
