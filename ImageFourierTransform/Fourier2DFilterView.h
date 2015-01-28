#ifndef FOURIER2DFILTERVIEW_H
#define FOURIER2DFILTERVIEW_H

#include "ComplexMatrix.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Fourier2DFilterView : public QGraphicsView
{
    Q_OBJECT

public:

    enum FilterType
    {
        NoFilter,
        LowPassFilter,
        HighPassFilter
    };

private:

    int m_filterValue;
    FilterType m_filterType;

    ComplexMatrix m_spectrum;
    double m_amplitudeMinimumDisplayThreshold;

    QGraphicsPixmapItem m_spectrumPixmapItem;
    QGraphicsPixmapItem m_filterPixmapItem;

public:

    explicit Fourier2DFilterView(QWidget* parent = 0);

public slots:

    void setSpectrum(const ComplexMatrix&);
    void setAmplitudeMinimumDisplayThreshold(double);

    void setFilterValue(int);
    void setFilterType(FilterType);

signals:

    void filterValueChanged(Fourier2DFilterView*, int);

private:

    void updateSpectrumPixmap();
    void updateFilterPixmap();

    void drawSpectrum(QPainter& painter, QWidget* viewport);
    void drawFilter(QPainter& painter, QWidget* viewport);

protected:

     void resizeEvent(QResizeEvent * event);
};

#endif // FOURIER2DFILTERVIEW_H
