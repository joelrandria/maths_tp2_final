#ifndef FOURIER2DFILTERVIEW_H
#define FOURIER2DFILTERVIEW_H

#include "ComplexMatrix.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Fourier2DFilterView : public QGraphicsView
{
    Q_OBJECT

public:

    enum FilterMode
    {
        NoFilter,
        LowPassFilter,
        HighPassFilter
    };

private:

    int m_filterValue;
    FilterMode m_filterMode;

    ComplexMatrix m_spectrum;
    double m_amplitudeMinimumDisplayThreshold;

    int m_shadowFilterValue;
    QGraphicsPixmapItem m_spectrumPixmapItem;
    QGraphicsPixmapItem m_filterPixmapItem;

public:

    explicit Fourier2DFilterView(QWidget* parent = 0);

public slots:

    void setSpectrum(const ComplexMatrix&);
    void setAmplitudeMinimumDisplayThreshold(double);

    void setFilterValue(int);
    void setFilterMode(FilterMode);

signals:

    void filterValueChanged(Fourier2DFilterView*, int);

private:

    double viewportHalfDiagonal() const;
    int filterValue(QMouseEvent* event) const;

    void updateSpectrumPixmap();
    void updateFilterPixmap();

    void drawSpectrum(QPainter& painter, QWidget* viewport);
    void drawFilter(QPainter& painter, QWidget* viewport);

protected:

    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void resizeEvent(QResizeEvent* event);
};

#endif // FOURIER2DFILTERVIEW_H
