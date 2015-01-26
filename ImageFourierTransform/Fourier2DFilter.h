#ifndef FOURIER2DFILTER_H
#define FOURIER2DFILTER_H

#include <QWidget>
#include <QPixmap>

#include "ComplexMatrix.h"

namespace Ui {
class Fourier2DFilter;
}

class Fourier2DFilter : public QWidget
{
    Q_OBJECT

private:

    Ui::Fourier2DFilter* ui;

    ComplexMatrix m_inputSpectrum;
    ComplexMatrix m_filteredSpectrum;

    QPixmap m_spectrumPixmap;

public:

    explicit Fourier2DFilter(QWidget *parent = 0);
    ~Fourier2DFilter();

    const ComplexMatrix& filteredSpectrum() const { return m_filteredSpectrum; }

    void setInputSpectrum(const ComplexMatrix& spectrum);

signals:

    void filteredSpectrumChanged(Fourier2DFilter*);

private slots:
    void on_amplitudeDisplayThresholdSlider_valueChanged(int value);

    void on_amplitudeDisplayThresholdSpinBox_valueChanged(double arg1);

private:

    void updateSpectrumView();
    void updateFilteredSpectrum();
};

#endif // FOURIER2DFILTER_H
