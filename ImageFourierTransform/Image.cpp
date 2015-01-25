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
    m_pow2SizedPixmap = image.m_pow2SizedPixmap;

    emit changed(this);

    return *this;
}

void Image::setPixmap(const QString &filename)
{
    m_pixmap.load(filename);

    m_pow2SizedPixmap = m_pixmap.scaled(pow(2, ceil(log2(m_pixmap.width()))),
                                        pow(2, ceil(log2(m_pixmap.height()))));

    emit changed(this);
}
