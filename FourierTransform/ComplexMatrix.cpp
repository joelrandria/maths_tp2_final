#include "ComplexMatrix.h"

#include <QDebug>

ComplexMatrix::ComplexMatrix()
{
}
ComplexMatrix::ComplexMatrix(const ComplexMatrix &mat)
{
    *this = mat;
}
ComplexMatrix::~ComplexMatrix()
{
}

ComplexMatrix &ComplexMatrix::operator=(const ComplexMatrix &mat)
{
    m_matrix = mat.m_matrix;

    return *this;
}

void ComplexMatrix::resize(int rows, int cols)
{
    int i;

    m_matrix.resize(rows);

    for (i = 0; i < rows; ++i)
        m_matrix[i].resize(cols);
}

void ComplexMatrix::transpose()
{
    int r;
    int c;
    int rowCount;
    int colCount;

    ComplexMatrix t;

    rowCount = rows();
    colCount = cols();

    t.resize(colCount, rowCount);

    for (r = 0; r < rowCount; ++r)
        for (c = 0; c < colCount; ++c)
            t.at(c, r) = at(r, c);

    *this = t;
}

void ComplexMatrix::print() const
{
    int r;
    int c;
    int rowCount;
    int colCount;

    QString rowValues;

    rowCount = rows();
    colCount = cols();

    for (r = 0; r < rowCount; ++r)
    {
        rowValues.clear();

        for (c = 0; c < colCount; ++c)
            rowValues += QString("<%1, %2> ").arg(m_matrix[r][c].real()).arg(m_matrix[r][c].imag());

        qDebug() << rowValues;
    }
}
