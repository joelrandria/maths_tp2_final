#ifndef FOURIER2DFILTERVIEW_H
#define FOURIER2DFILTERVIEW_H

#include "ComplexMatrix.h"

#include <QGraphicsView>

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
    QImage m_spectrumImage;
    double m_amplitudeMinimumDisplayThreshold;

public:

    explicit Fourier2DFilterView(QWidget* parent = 0);

    void paintEvent(QPaintEvent* event);

public slots:

    void setSpectrum(const ComplexMatrix&);
    void setAmplitudeMinimumDisplayThreshold(double);

    void setFilterValue(int);
    void setFilterType(FilterType);

signals:

    void filterValueChanged(Fourier2DFilterView*, int);

private:

    void updateSpectrumImage();
};

#endif // FOURIER2DFILTERVIEW_H
