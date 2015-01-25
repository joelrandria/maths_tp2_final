#ifndef COMPLEXMATRIX_H
#define COMPLEXMATRIX_H

#include "Fourier.h"

#include <vector>

class ComplexMatrix
{
private:

    std::vector<ComplexVector> m_matrix;

public:

    ComplexMatrix();
    ComplexMatrix(const ComplexMatrix& mat);
    ~ComplexMatrix();

    int rows() const { return (int)m_matrix.size(); }
    int cols() const { return m_matrix.size() > 0 ? (int)m_matrix[0].size() : 0; }

    ComplexVector& at(int row) { return m_matrix[row]; }
    const ComplexVector& at(int row) const { return m_matrix[row]; }
    Complex& at(int row, int col) { return m_matrix[row][col]; }

    void resize(int rows, int cols);
    void transpose();

    void print() const;

    ComplexMatrix& operator=(const ComplexMatrix& mat);
};

#endif // COMPLEXMATRIX_H
