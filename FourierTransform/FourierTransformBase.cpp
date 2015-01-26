#include "FourierTransformBase.h"

void FourierTransformBase::transform2D(const ComplexMatrix &signalValues, ComplexMatrix &spectralValues)
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
void FourierTransformBase::inverseTransform2D(const ComplexMatrix &spectralValues, ComplexMatrix &signalValues)
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
