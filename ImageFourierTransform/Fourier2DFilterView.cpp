#include "Fourier2DFilterView.h"

#include <QBitmap>
#include <QGraphicsBlurEffect>

Fourier2DFilterView::Fourier2DFilterView(QWidget* parent)
    :QGraphicsView(parent),
      m_filterValue(50),
      m_filterType(NoFilter),
      m_amplitudeMinimumDisplayThreshold(0.025f)
{
    QGraphicsBlurEffect* blurEffect;
    blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(2);
    viewport()->setGraphicsEffect(blurEffect);
}

void Fourier2DFilterView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    drawSpectrum(painter, viewport());
    drawFilter(painter, viewport());
}
void Fourier2DFilterView::drawSpectrum(QPainter& painter, QWidget* viewport)
{
    painter.drawImage(viewport->rect(), m_spectrumImage);
}
void Fourier2DFilterView::drawFilter(QPainter& painter, QWidget* viewport)
{
    int ellipseRx;
    int ellipseRy;
    QPoint ellipseCenter;

    ellipseRx = viewport->width() * m_filterValue / 200;
    ellipseRy = viewport->height() * m_filterValue / 200;
    ellipseCenter = QPoint(viewport->width() / 2, viewport->height() / 2);

    QBitmap mask(viewport->size());
    mask.fill(Qt::color1);

    QPainter maskPainter(&mask);
    maskPainter.setPen(Qt::color0);
    maskPainter.drawEllipse(ellipseCenter, ellipseRx, ellipseRy);

    QImage areaImage(viewport->size(), QImage::Format_ARGB32);
    areaImage.fill(qRgba(50, 50, 50, 180));

    QPixmap areaPixmap = QPixmap::fromImage(areaImage);
    areaPixmap.setMask(mask);

    painter.drawPixmap(viewport->rect(), areaPixmap);
}

void Fourier2DFilterView::setSpectrum(const ComplexMatrix& spectrum)
{
    m_spectrum = spectrum;

    updateSpectrumImage();
}
void Fourier2DFilterView::setAmplitudeMinimumDisplayThreshold(double threshold)
{
    m_amplitudeMinimumDisplayThreshold = threshold;

    updateSpectrumImage();
}

void Fourier2DFilterView::setFilterValue(int value)
{
    m_filterValue = value;

    viewport()->update();
}
void Fourier2DFilterView::setFilterType(FilterType type)
{
    m_filterType = type;

    viewport()->update();
}

void Fourier2DFilterView::updateSpectrumImage()
{
    int r;
    int c;
    int rowCount;
    int colCount;

    static QRgb black = qRgb(0, 0, 0);
    static QRgb white = qRgb(255, 255, 255);

    rowCount = m_spectrum.rows();
    colCount = m_spectrum.cols();

    m_spectrumImage = QImage(colCount, rowCount, QImage::Format_RGB32);

    for (r = 0; r < rowCount; ++r)
    {
        for (c = 0; c < colCount; ++c)
        {
            if (fabs(m_spectrum.at(r, c).real()) > m_amplitudeMinimumDisplayThreshold)
                m_spectrumImage.setPixel(c, r, white);
            else
                m_spectrumImage.setPixel(c, r, black);
        }
    }

    viewport()->update();
}
