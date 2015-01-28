#include "Fourier2DFilterView.h"

#include <QBitmap>
#include <QMouseEvent>
#include <QGraphicsBlurEffect>

#include <cmath>

Fourier2DFilterView::Fourier2DFilterView(QWidget* parent)
    :QGraphicsView(parent),
      m_filterValue(50),
      m_filterMode(NoFilter),
      m_amplitudeMinimumDisplayThreshold(0.025f),
      m_shadowFilterValue(m_filterValue)
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
    if (m_amplitudeMinimumDisplayThreshold != threshold)
    {
        m_amplitudeMinimumDisplayThreshold = threshold;

        updateSpectrumPixmap();
    }
}

void Fourier2DFilterView::setFilterValue(int value)
{
    if (m_filterValue != value)
    {
        m_filterValue = value;
        m_shadowFilterValue = value;

        updateFilterPixmap();

        emit filterValueChanged(this, value);
    }
}
void Fourier2DFilterView::setFilterMode(FilterMode mode)
{
    if (m_filterMode != mode)
    {
        m_filterMode = mode;

        updateFilterPixmap();
    }
}

double Fourier2DFilterView::viewportHalfDiagonal() const
{
    return (hypot(viewport()->width(), viewport()->height()) / 2);
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

    if (rowCount > 0 && colCount > 0)
    {
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
}
void Fourier2DFilterView::updateFilterPixmap()
{
    int ellipseRx;
    int ellipseRy;
    QPoint ellipseCenter;

    QBitmap mask;
    QImage areaImage;
    QPixmap areaPixmap;

    if (m_filterMode != NoFilter)
    {
        ellipseRx = viewportHalfDiagonal() * m_shadowFilterValue / 100;
        ellipseRy = viewportHalfDiagonal() * m_shadowFilterValue / 100;
        ellipseCenter = QPoint(viewport()->width() / 2, viewport()->height() / 2);
        mask = QBitmap(viewport()->size());
        mask.fill(m_filterMode == LowPassFilter ? Qt::color1 : Qt::color0);

        QPainter maskPainter(&mask);
        maskPainter.setBrush(m_filterMode == LowPassFilter ? Qt::color0 : Qt::color1);
        maskPainter.drawEllipse(ellipseCenter, ellipseRx, ellipseRy);

        areaImage = QImage(viewport()->size(), QImage::Format_ARGB32);
        areaImage.fill(qRgba(50, 50, 50, 180));

        areaPixmap = QPixmap::fromImage(areaImage);
        areaPixmap.setMask(mask);
    }

    m_filterPixmapItem.setPixmap(areaPixmap);
}

int Fourier2DFilterView::filterValue(QMouseEvent* event) const
{
    int value;
    QPointF viewportCenter;
    double eventCenterDistance;

    viewportCenter = QPointF(viewport()->width() / 2, viewport()->height() / 2);
    eventCenterDistance = hypot(event->pos().x() - viewportCenter.x(), event->pos().y() - viewportCenter.y());
    value = eventCenterDistance * 100 / viewportHalfDiagonal();

    return (value <= 100 ? value : 100);
}
void Fourier2DFilterView::mouseMoveEvent(QMouseEvent* event)
{
    m_shadowFilterValue = filterValue(event);

    updateFilterPixmap();
}
void Fourier2DFilterView::mouseReleaseEvent(QMouseEvent* event)
{
    setFilterValue(filterValue(event));
}

void Fourier2DFilterView::resizeEvent(QResizeEvent*)
{
    updateSpectrumPixmap();
    updateFilterPixmap();

    scene()->update(scene()->sceneRect());
}
