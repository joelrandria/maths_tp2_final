#include "Fourier2DFilterView.h"

#include <QBitmap>
#include <QGraphicsBlurEffect>

Fourier2DFilterView::Fourier2DFilterView(QWidget* parent)
    :QGraphicsView(parent),
      m_filterValue(50),
      m_filterType(NoFilter),
      m_amplitudeMinimumDisplayThreshold(0.025f)
{
    QGraphicsBlurEffect* effect;

    effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(2.5f);
    m_spectrumPixmapItem.setGraphicsEffect(effect);

    setScene(new QGraphicsScene());
    scene()->addItem(&m_spectrumPixmapItem);
    scene()->addItem(&m_filterPixmapItem);
}

void Fourier2DFilterView::setSpectrum(const ComplexMatrix& spectrum)
{
    m_spectrum = spectrum;

    updateSpectrumPixmap();
}
void Fourier2DFilterView::setAmplitudeMinimumDisplayThreshold(double threshold)
{
    m_amplitudeMinimumDisplayThreshold = threshold;

    updateSpectrumPixmap();
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

void Fourier2DFilterView::updateSpectrumPixmap()
{
    int r;
    int c;
    int rowCount;
    int colCount;

    static QRgb black = qRgb(0, 0, 0);
    static QRgb white = qRgb(255, 255, 255);

    rowCount = m_spectrum.rows();
    colCount = m_spectrum.cols();

    QImage spectrumImage = QImage(colCount, rowCount, QImage::Format_RGB32);

    for (r = 0; r < rowCount; ++r)
    {
        for (c = 0; c < colCount; ++c)
        {
            if (fabs(m_spectrum.at(r, c).real()) > m_amplitudeMinimumDisplayThreshold)
                spectrumImage.setPixel(c, r, white);
            else
                spectrumImage.setPixel(c, r, black);
        }
    }

    m_spectrumPixmapItem.setPixmap(QPixmap::fromImage(spectrumImage).scaled(viewport()->size()));
}
void Fourier2DFilterView::updateFilterPixmap()
{
    int ellipseRx;
    int ellipseRy;
    QPoint ellipseCenter;

    QBitmap mask;
    QImage areaImage;
    QPixmap areaPixmap;

    ellipseRx = viewport()->width() * m_filterValue / 200;
    ellipseRy = viewport()->height() * m_filterValue / 200;
    ellipseCenter = QPoint(viewport()->width() / 2, viewport()->height() / 2);

    mask = QBitmap(viewport()->size());
    mask.fill(Qt::color1);

    QPainter maskPainter(&mask);
    maskPainter.setPen(Qt::color0);
    maskPainter.drawEllipse(ellipseCenter, ellipseRx, ellipseRy);

    areaImage = QImage(viewport()->size(), QImage::Format_ARGB32);
    areaImage.fill(qRgba(50, 50, 50, 180));

    areaPixmap = QPixmap::fromImage(areaImage);
    areaPixmap.setMask(mask);

    m_filterPixmapItem.setPixmap(areaPixmap);
}

void Fourier2DFilterView::resizeEvent(QResizeEvent *event)
{
    updateSpectrumPixmap();
    updateFilterPixmap();

    scene()->update(scene()->sceneRect());
}
