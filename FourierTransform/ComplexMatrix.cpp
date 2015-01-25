#include "ComplexMatrix.h"

#include <QDebug>

ComplexMatrix::ComplexMatrix()
    :m_alignment(LowFrequencyMajorAlignment)
{
}
ComplexMatrix::ComplexMatrix(const ComplexMatrix& mat)
{
    *this = mat;
}
ComplexMatrix::~ComplexMatrix()
{
}

ComplexMatrix& ComplexMatrix::operator=(const ComplexMatrix& mat)
{
    m_matrix = mat.m_matrix;
    m_alignment = mat.m_alignment;

    return *this;
}

void ComplexMatrix::setAlignment(SpectrumAlignment alignment)
{
    int rowCount;
    int colCount;
    int rowHalfCount;
    int colHalfCount;

    ComplexMatrix aligned;

    if (m_alignment == alignment)
        return;

    rowCount = rows();
    colCount = cols();
    rowHalfCount = rowCount / 2;
    colHalfCount = colCount / 2;

    aligned.resize(rowCount, colCount);
    aligned.m_alignment = alignment;

    blit(*this, 0, 0, rowHalfCount, colHalfCount, aligned, rowHalfCount, colHalfCount);
    blit(*this, 0, colHalfCount, rowHalfCount, colHalfCount, aligned, rowHalfCount, 0);
    blit(*this, rowHalfCount, 0, rowHalfCount, colHalfCount, aligned, 0, colHalfCount);
    blit(*this, rowHalfCount, colHalfCount, rowHalfCount, colHalfCount, aligned, 0, 0);

    *this = aligned;
}
void ComplexMatrix::blit(const ComplexMatrix &src, int srcStartRow, int srcStartCol,
                         int rowCount, int colCount,
                         ComplexMatrix &dst, int dstStartRow, int dstStartCol)
{
    int r;
    int c;

    for (r = 0; r < rowCount; ++r)
        for (c = 0; c < colCount; ++c)
            dst.at(dstStartRow + r, dstStartCol + c) = src.at(srcStartRow + r, srcStartCol + c);
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
