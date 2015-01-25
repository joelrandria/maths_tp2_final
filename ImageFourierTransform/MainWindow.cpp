#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_baseImage, SIGNAL(changed(Image*)), this, SLOT(onBaseImageChanged(Image*)));
    connect(ui->fourier2DFilter, SIGNAL(filteredSpectrumChanged(Fourier2DFilter*)), this, SLOT(onFilteredSpectrumChanged(Fourier2DFilter*)));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fd(this, tr("Ouvrir une image"));
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setNameFilter(tr("Portable Graymap (*.pgm)"));

    if (fd.exec())
        m_baseImage.load(fd.selectedFiles().first());
}

void MainWindow::onBaseImageChanged(Image *)
{
    ComplexMatrix spectrumMatrix;

    ui->baseImageLabel->setPixmap(m_baseImage.pixmap());

    m_fft.transform(m_baseImage.signalMatrix(), spectrumMatrix);

    ui->fourier2DFilter->setInputSpectrum(spectrumMatrix);
}

void MainWindow::onFilteredSpectrumChanged(Fourier2DFilter *)
{
    ComplexMatrix filteredSignalMatrix;

    m_fft.inverseTransform(ui->fourier2DFilter->filteredSpectrum(), filteredSignalMatrix);

    m_filteredImage.load(filteredSignalMatrix, m_baseImage.pixmap().width(), m_baseImage.pixmap().height());
    ui->filteredImageLabel->setPixmap(m_filteredImage.pixmap());
}
