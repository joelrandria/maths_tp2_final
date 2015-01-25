#include "FourierTransform.h"

#include <stdexcept>
#include <stdio.h>

void FourierTransform::transform(const ComplexVector& signalValues, ComplexVector& spectralValues)
{
    int valueCount;
    int rangeStart;
    int rangeEnd;

    Complex sum;

    if (signalValues.size() != spectralValues.size())
        throw std::invalid_argument("FourierTransform::transform(): Les vecteurs spécifiés doivent être de mêmes tailles");

    valueCount = signalValues.size();

    rangeStart = -valueCount / 2;
    rangeEnd = valueCount % 2 ? valueCount / 2 : (valueCount / 2) - 1;
    ++rangeEnd;

    for (int m = rangeStart; m < rangeEnd; ++m)
    {
        sum = 0;

        for (int n = 0; n < (int)signalValues.size(); ++n)
            sum += signalValues[n] * exp(Complex(0, -2 * M_PI * m * n / (int)signalValues.size()));

        spectralValues[m >= 0 ? m : valueCount + m] = sum / (double)valueCount;
    }
}
void FourierTransform::inverseTransform(const ComplexVector& spectralValues, ComplexVector& signalValues)
{
    int i;
    int valueCount;
    int rangeStart;
    int rangeEnd;

    Complex sum;
    Complex sm;

    if (signalValues.size() != spectralValues.size())
        throw std::invalid_argument("FourierTransform::inverseTransform(): Les vecteurs spécifiés doivent être de mêmes tailles");

    valueCount = spectralValues.size();

    rangeStart = -valueCount / 2;
    rangeEnd = valueCount % 2 ? valueCount / 2 : (valueCount / 2) - 1;
    ++rangeEnd;

    i = 0;

    for (int n = 0; n < valueCount; ++n)
    {
        sum = 0;

        for (int m = rangeStart; m < rangeEnd; ++m)
        {
            sm = 0;

            if (m >= 0)
                sm = spectralValues[m];
            else
                sm = spectralValues[valueCount + m];

            sum += sm * exp(Complex(0, 2 * M_PI * m * n / valueCount));
        }

        signalValues[i++] = sum;
    }
}
