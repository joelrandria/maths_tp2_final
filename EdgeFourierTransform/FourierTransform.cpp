#include "FourierTransform.h"

#include <stdexcept>
#include <stdio.h>

void FourierTransform::transform(const ComplexVector &baseValues, ComplexVector &transformedValues)
{
    int valueCount;
    int rangeStart;
    int rangeEnd;

    Complex sum;

    if (baseValues.size() != transformedValues.size())
        throw std::invalid_argument("FourierTransform::transform(): Les vecteurs spécifiés doivent être de mêmes tailles");

    valueCount = baseValues.size();

    rangeStart = -valueCount / 2;
    rangeEnd = valueCount % 2 ? valueCount / 2 : (valueCount / 2) - 1;
    ++rangeEnd;

    for (int m = rangeStart; m < rangeEnd; ++m)
    {
        sum = 0;

        for (int n = 0; n < (int)baseValues.size(); ++n)
            sum += baseValues[n] * exp(Complex(0, -2 * M_PI * m * n / (int)baseValues.size()));

        transformedValues[m >= 0 ? m : valueCount + m] = sum / (double)valueCount;
    }
}
void FourierTransform::inverseTransform(const ComplexVector &transformedValues, ComplexVector &baseValues)
{
    int i;
    int valueCount;
    int rangeStart;
    int rangeEnd;

    Complex sum;
    Complex sm;

    if (baseValues.size() != transformedValues.size())
        throw std::invalid_argument("FourierTransform::inverseTransform(): Les vecteurs spécifiés doivent être de mêmes tailles");

    valueCount = transformedValues.size();

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
                sm = transformedValues[m];
            else
                sm = transformedValues[valueCount + m];

            sum += sm * exp(Complex(0, 2 * M_PI * m * n / valueCount));
        }

        baseValues[i++] = sum;
    }
}
