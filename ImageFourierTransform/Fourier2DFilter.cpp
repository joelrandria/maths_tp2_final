#include "Fourier2DFilter.h"
#include "ui_Fourier2DFilter.h"

#include "FourierLowPassFilter.h"
#include "FourierHighPassFilter.h"

Fourier2DFilter::Fourier2DFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fourier2DFilter)
{
    ui->setupUi(this);

    m_filters[0] = new FourierLowPassFilter();
    m_filters[1] = new FourierHighPassFilter();

    connect(ui->spectrumView, SIGNAL(filterValueChanged(Fourier2DFilterView*,int)), this, SLOT(onSpectrumViewFilterValueChanged(Fourier2DFilterView*, int)));
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
    FourierPassFilterBase* activeFilter;

    activeFilter = 0;

    m_filteredSpectrum = m_inputSpectrum;

    if (ui->filterSettingsGroupBox->isChecked())
        activeFilter = m_filters[ui->filterTypeComboBox->currentIndex()];

    if (activeFilter)
    {
        activeFilter->setThreshold(ui->filterValueSpinBox->value());
        activeFilter->filter2D(m_filteredSpectrum);
    }

    m_filteredSpectrum.setAlignment(ComplexMatrix::LowFrequencyMajorAlignment);

    emit filteredSpectrumChanged(this, m_filteredSpectrum);
}

void Fourier2DFilter::on_filterSettingsGroupBox_toggled(bool enabled)
{
    Fourier2DFilterView::FilterMode mode;

    mode = Fourier2DFilterView::NoFilter;

    if (enabled)
    {
        if (ui->filterTypeComboBox->currentIndex() == 0)
            mode = Fourier2DFilterView::LowPassFilter;
        else
            mode = Fourier2DFilterView::HighPassFilter;
    }

    ui->spectrumView->setFilterMode(mode);

    updateFilteredSpectrum();
}
void Fourier2DFilter::on_filterTypeComboBox_currentIndexChanged(int index)
{
    Fourier2DFilterView::FilterMode mode;

    mode = Fourier2DFilterView::NoFilter;

    if (index == 0)
        mode = Fourier2DFilterView::LowPassFilter;
    else
        mode = Fourier2DFilterView::HighPassFilter;

    ui->spectrumView->setFilterMode(mode);

    updateFilteredSpectrum();
}
void Fourier2DFilter::on_filterValueSpinBox_valueChanged(int value)
{
    ui->spectrumView->setFilterValue(value);

    updateFilteredSpectrum();
}
void Fourier2DFilter::onSpectrumViewFilterValueChanged(Fourier2DFilterView*, int value)
{
    ui->filterValueSpinBox->setValue(value);
}

void Fourier2DFilter::on_amplitudeDisplayThresholdSlider_valueChanged(int value)
{
    ui->amplitudeDisplayThresholdSpinBox->setValue((double)value / 1000);
}
void Fourier2DFilter::on_amplitudeDisplayThresholdSpinBox_valueChanged(double arg1)
{
    ui->amplitudeDisplayThresholdSlider->setValue(arg1 * 1000);
}
