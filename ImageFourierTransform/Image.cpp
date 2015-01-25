#include "Image.h"

#include <cmath>

Image::Image()
    :QObject()
{
}
Image::Image(const Image& image)
    :QObject()
{
    *this = image;
}
Image::~Image()
{
}

Image& Image::operator=(const Image& image)
{
    m_pixmap = image.m_pixmap;

    m_pow2ScaledPixmap = image.m_pow2ScaledPixmap;
    m_pow2ScaledImage = image.m_pow2ScaledImage;

    m_signalMatrix = image.m_signalMatrix;

    emit changed(this);

    return *this;
}

void Image::load(const QString& filename)
{
    m_pixmap.load(filename);

    m_pow2ScaledPixmap = m_pixmap.scaled(pow(2, ceil(log2(m_pixmap.width()))), pow(2, ceil(log2(m_pixmap.height()))));
    m_pow2ScaledImage = m_pow2ScaledPixmap.toImage();

    updateSignalMatrix();

    emit changed(this);
}
void Image::load(const ComplexMatrix& matrix, int width, int height)
{
    int r;
    int c;
    int g;
    int rowCount;
    int colCount;

    m_signalMatrix = matrix;

    rowCount = m_signalMatrix.rows();
    colCount = m_signalMatrix.cols();

    m_pow2ScaledImage = QImage(colCount, rowCount, QImage::Format_RGB32);

    for (r = 0; r < rowCount; ++r)
    {
        for (c = 0; c < colCount; ++c)
        {
            g = m_signalMatrix.at(r, c).real();
            m_pow2ScaledImage.setPixel(c, r, qRgb(g, g, g));
        }
    }

    m_pow2ScaledPixmap = QPixmap::fromImage(m_pow2ScaledImage);
    m_pixmap = m_pow2ScaledPixmap.scaled(width, height);
}

void Image::updateSignalMatrix()
{
    int r;
    int c;
    int rows;
    int cols;

    rows = m_pow2ScaledPixmap.height();
    cols = m_pow2ScaledPixmap.width();

    m_signalMatrix.resize(rows, cols);

    for (r = 0; r < rows; ++r)
        for (c = 0; c < cols; ++c)
            m_signalMatrix.at(r, c) = Complex(qGray(m_pow2ScaledImage.pixel(c, r)), 0);
}
