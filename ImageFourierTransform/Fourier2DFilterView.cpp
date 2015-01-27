#include "Fourier2DFilterView.h"

#include <QGraphicsBlurEffect>

Fourier2DFilterView::Fourier2DFilterView(QWidget* parent)
    :QGraphicsView(parent),
      m_filterValue(50),
      m_filterType(NoFilter),
      m_amplitudeMinimumDisplayThreshold(0.025f)
{
    QGraphicsBlurEffect* effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(2.5f);

    viewport()->setGraphicsEffect(effect);
}

void Fourier2DFilterView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    painter.drawImage(viewport()->rect(), m_spectrumImage);
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
