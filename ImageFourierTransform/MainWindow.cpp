#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Fourier2DFilter.h"
#include "FastFourierTransform.h"

#include <QFileDialog>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->basePictureGraphicsView->setScene(new QGraphicsScene());
    ui->filteredPictureGraphicsView->setScene(new QGraphicsScene());

    connect(&m_baseImage, SIGNAL(changed(Image*)), this, SLOT(onBaseImageChanged(Image*)));
    connect(&m_spectrumFilter, SIGNAL(filteredSpectrumChanged(Fourier2DFilter*, ComplexMatrix&)), this, SLOT(onFilteredSpectrumChanged(Fourier2DFilter*, ComplexMatrix&)));
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
void MainWindow::on_actionShowSpectrumFilter_triggered()
{
    m_spectrumFilter.show();
}

void MainWindow::onBaseImageChanged(Image *)
{
    ComplexMatrix spectrumMatrix;

    ui->basePictureGraphicsView->scene()->clear();
    ui->basePictureGraphicsView->scene()->addPixmap(m_baseImage.pixmap());

    m_fft.transform2D(m_baseImage.signalMatrix(), spectrumMatrix);

    m_spectrumFilter.setInputSpectrum(spectrumMatrix);

    updatePictureViewLayouts();
}

void MainWindow::onFilteredSpectrumChanged(Fourier2DFilter*, ComplexMatrix& filteredSpectrum)
{
    ComplexMatrix filteredSignalMatrix;

    m_fft.inverseTransform2D(filteredSpectrum, filteredSignalMatrix);

    m_filteredImage.load(filteredSignalMatrix, m_baseImage.pixmap().width(), m_baseImage.pixmap().height());

    ui->filteredPictureGraphicsView->scene()->clear();
    ui->filteredPictureGraphicsView->scene()->addPixmap(m_filteredImage.pixmap());

    updatePictureViewLayouts();
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    updatePictureViewLayouts();
}

void MainWindow::on_fitPicturesToWindowCheckBox_clicked(bool)
{
    updatePictureViewLayouts();
}

void MainWindow::updatePictureViewLayouts()
{
    if (ui->fitPicturesToWindowCheckBox->isChecked())
    {
        if (!ui->basePictureGraphicsView->scene()->items().isEmpty())
        {
            ui->basePictureGraphicsView->setSceneRect(m_baseImage.pixmap().rect());
            ui->basePictureGraphicsView->fitInView(ui->basePictureGraphicsView->scene()->items().first());

            ui->filteredPictureGraphicsView->setSceneRect(m_filteredImage.pixmap().rect());
            ui->filteredPictureGraphicsView->fitInView(ui->filteredPictureGraphicsView->scene()->items().first());
        }
    }
    else
    {
        ui->basePictureGraphicsView->resetMatrix();
        ui->filteredPictureGraphicsView->resetMatrix();
    }
}
