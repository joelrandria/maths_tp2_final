#include "Image.h"

#include <cmath>

Image::Image()
    :QObject()
{
}
Image::Image(const Image &image)
    :QObject()
{
    *this = image;
}
Image::~Image()
{
}

Image &Image::operator=(const Image &image)
{
    m_pixmap = image.m_pixmap;

    m_pow2ScaledPixmap = image.m_pow2ScaledPixmap;
    m_pow2ScaledImage = image.m_pow2ScaledImage;

    m_signalMatrix = image.m_signalMatrix;

    emit changed(this);

    return *this;
}

void Image::setPixmap(const QString &filename)
{
    m_pixmap.load(filename);

    m_pow2ScaledPixmap = m_pixmap.scaled(pow(2, ceil(log2(m_pixmap.width()))),
                                        pow(2, ceil(log2(m_pixmap.height()))));
    m_pow2ScaledImage = m_pow2ScaledPixmap.toImage();

    updateSignalMatrix();

    emit changed(this);
}

void Image::updateSignalMatrix()
{
    int r;
    int c;
    int rows;
    int cols;

    rows = m_pixmap.height();
    cols = m_pixmap.width();

    m_signalMatrix.resize(rows, cols);

    for (r = 0; r < rows; ++r)
        for (c = 0; c < cols; ++c)
            m_signalMatrix.at(r, c) = Complex(qGray(m_pow2ScaledImage.pixel(c, r)), 0);
}
