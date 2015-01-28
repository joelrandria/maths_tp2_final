#ifndef COMPLEXMATRIX_H
#define COMPLEXMATRIX_H

#include "Fourier.h"

#include <vector>

class ComplexMatrix
{
public:

    enum SpectrumAlignment
    {
        HighFrequencyMajorAlignment,
        LowFrequencyMajorAlignment
    };

private:

    std::vector<ComplexVector> m_matrix;
    SpectrumAlignment m_alignment;

public:

    ComplexMatrix();
    ComplexMatrix(const ComplexMatrix& mat);
    ~ComplexMatrix();

    SpectrumAlignment alignment() const { return m_alignment; }
    void setAlignment(SpectrumAlignment alignment);

    bool isEmpty() const { return rows() == 0 && cols() == 0; }
    int rows() const { return (int)m_matrix.size(); }
    int cols() const { return m_matrix.size() > 0 ? (int)m_matrix[0].size() : 0; }

    ComplexVector& at(int row) { return m_matrix[row]; }
    const ComplexVector& at(int row) const { return m_matrix[row]; }

    Complex& at(int row, int col) { return m_matrix[row][col]; }
    const Complex& at(int row, int col) const { return m_matrix[row][col]; }

    void resize(int rows, int cols);
    void transpose();

    void print() const;

    ComplexMatrix& operator=(const ComplexMatrix& mat);

private:

    static void blit(const ComplexMatrix& src, int srcStartRow, int srcStartCol,
                     int rowCount, int colCount,
                     ComplexMatrix& dst, int dstStartRow, int dstStartCol);
};

#endif // COMPLEXMATRIX_H
