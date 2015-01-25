#ifndef IMAGE_H
#define IMAGE_H

#include "ComplexMatrix.h"

#include <QPixmap>
#include <QObject>

class Image : public QObject
{
    Q_OBJECT

private:

    QPixmap m_pixmap;

    QPixmap m_pow2ScaledPixmap;
    QImage m_pow2ScaledImage;

    ComplexMatrix m_signalMatrix;

public:

    Image();
    Image(const Image& image);
    ~Image();

    const QPixmap& pixmap() const { return m_pixmap; }
    const QPixmap& pow2SizedPixmap() const { return m_pow2ScaledPixmap; }
    const ComplexMatrix& signalMatrix() const { return m_signalMatrix; }

    void load(const QString& filename);
    void load(const ComplexMatrix& matrix, int width, int height);

    Image& operator=(const Image& image);

signals:

    void changed(Image*);

private:

    void updateSignalMatrix();
};

#endif // IMAGE_H
