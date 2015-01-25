#include "Fourier2DFilter.h"
#include "ui_Fourier2DFilter.h"

#include <QGraphicsBlurEffect>

Fourier2DFilter::Fourier2DFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fourier2DFilter)
{
    ui->setupUi(this);
    ui->spectrumImageLabel->setGraphicsEffect(new QGraphicsBlurEffect());
}
Fourier2DFilter::~Fourier2DFilter()
{
    delete ui;
}

void Fourier2DFilter::setInputSpectrum(const ComplexMatrix& spectrum)
{
    m_inputSpectrum = spectrum;
    m_inputSpectrum.setAlignment(ComplexMatrix::HighFrequencyMajorAlignment);

    updateSpectrumView();
    updateFilteredSpectrum();
}

void Fourier2DFilter::updateSpectrumView()
{
    int r;
    int c;
    int rowCount;
    int colCount;

    rowCount = m_inputSpectrum.rows();
    colCount = m_inputSpectrum.cols();

    QImage spectrumImage(colCount, rowCount, QImage::Format_RGB32);

    for (r = 0; r < rowCount; ++r)
    {
        for (c = 0; c < colCount; ++c)
        {
            if (fabs(m_inputSpectrum.at(r, c).real()) > 0.025f)
                spectrumImage.setPixel(c, r, qRgb(255, 255, 255));
            else
                spectrumImage.setPixel(c, r, qRgb(0, 0, 0));
        }
    }

    m_spectrumPixmap = QPixmap::fromImage(spectrumImage);
    ui->spectrumImageLabel->setPixmap(m_spectrumPixmap);
}

void Fourier2DFilter::updateFilteredSpectrum()
{
    m_filteredSpectrum = m_inputSpectrum;
    m_filteredSpectrum.setAlignment(ComplexMatrix::LowFrequencyMajorAlignment);

    emit filteredSpectrumChanged(this);
}
