#ifndef FOURIER2DFILTER_H
#define FOURIER2DFILTER_H

#include <QWidget>

#include "ComplexMatrix.h"

namespace Ui {
class Fourier2DFilter;
}

class Fourier2DFilterView;
class FourierPassFilterBase;

class Fourier2DFilter : public QWidget
{
    Q_OBJECT

private:

    Ui::Fourier2DFilter* ui;

    ComplexMatrix m_inputSpectrum;
    ComplexMatrix m_filteredSpectrum;

    FourierPassFilterBase* m_filters[2];

public:

    explicit Fourier2DFilter(QWidget *parent = 0);
    ~Fourier2DFilter();

    const ComplexMatrix& filteredSpectrum() const { return m_filteredSpectrum; }

    void setInputSpectrum(const ComplexMatrix& spectrum);

signals:

    void filteredSpectrumChanged(Fourier2DFilter*, ComplexMatrix&);

private slots:

    void on_filterSettingsGroupBox_toggled(bool);
    void on_filterValueSpinBox_valueChanged(int value);
    void onSpectrumViewFilterValueChanged(Fourier2DFilterView*, int);

    void on_amplitudeDisplayThresholdSlider_valueChanged(int);
    void on_amplitudeDisplayThresholdSpinBox_valueChanged(double);

    void on_filterTypeComboBox_currentIndexChanged(int index);

private:

    void updateFilteredSpectrum();
};

#endif // FOURIER2DFILTER_H
