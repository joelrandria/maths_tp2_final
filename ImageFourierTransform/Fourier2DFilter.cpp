#include "Fourier2DFilter.h"
#include "ui_Fourier2DFilter.h"

Fourier2DFilter::Fourier2DFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fourier2DFilter)
{
    ui->setupUi(this);

    connect(ui->amplitudeDisplayThresholdSpinBox, SIGNAL(valueChanged(double)), ui->spectrumView, SLOT(setAmplitudeMinimumDisplayThreshold(double)));
}
Fourier2DFilter::~Fourier2DFilter()
{
    delete ui;
}

void Fourier2DFilter::setInputSpectrum(const ComplexMatrix& spectrum)
{
    m_inputSpectrum = spectrum;
    m_inputSpectrum.setAlignment(ComplexMatrix::HighFrequencyMajorAlignment);

    ui->spectrumView->setSpectrum(m_inputSpectrum);

    updateFilteredSpectrum();
}

void Fourier2DFilter::updateFilteredSpectrum()
{
    m_filteredSpectrum = m_inputSpectrum;
    m_filteredSpectrum.setAlignment(ComplexMatrix::LowFrequencyMajorAlignment);

    emit filteredSpectrumChanged(this, m_filteredSpectrum);
}

void Fourier2DFilter::on_amplitudeDisplayThresholdSlider_valueChanged(int value)
{
    ui->amplitudeDisplayThresholdSpinBox->setValue((double)value / 1000);
}
void Fourier2DFilter::on_amplitudeDisplayThresholdSpinBox_valueChanged(double arg1)
{
    ui->amplitudeDisplayThresholdSlider->setValue(arg1 * 1000);
}
