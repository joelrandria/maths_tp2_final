#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_baseImage, SIGNAL(changed(Image*)), this, SLOT(onBaseImageChanged(Image*)));
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
        m_baseImage.setPixmap(fd.selectedFiles().first());
}
void MainWindow::onBaseImageChanged(Image *)
{
    ui->baseImageLabel->setPixmap(m_baseImage.pixmap());

    ////////////////////////////////////////////////////////////////////////////////////

    ComplexMatrix signalMatrix = m_baseImage.signalMatrix();

    qDebug() << "----- Signal -----";
    signalMatrix.print();
    qDebug() << "------------------------------------";

    ComplexMatrix transformMatrix;
    transformMatrix.resize(signalMatrix.rows(), signalMatrix.cols());

    m_fft.transform(signalMatrix, transformMatrix);

    qDebug() << "----- Transformée -----";
    transformMatrix.print();
    qDebug() << "------------------------------------";

    ComplexMatrix inverseTransformMatrix;
    transformMatrix.resize(signalMatrix.rows(), signalMatrix.cols());

    m_fft.inverseTransform(transformMatrix, inverseTransformMatrix);

    qDebug() << "----- Transformée inverse -----";
    inverseTransformMatrix.print();
    qDebug() << "------------------------------------";

    ////////////////////////////////////////////////////////////////////////////////////
}
