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
        m_baseImage.load(fd.selectedFiles().first());
}
void MainWindow::onBaseImageChanged(Image *)
{
    ui->baseImageLabel->setPixmap(m_baseImage.pixmap());

    ////////////////////////////////////////////////////////////////////////////////////

    ComplexMatrix signalMatrix = m_baseImage.signalMatrix();

    ComplexMatrix transformMatrix;
    transformMatrix.resize(signalMatrix.rows(), signalMatrix.cols());

    m_fft.transform(signalMatrix, transformMatrix);
    updateTransformView(transformMatrix);

    ComplexMatrix inverseTransformMatrix;
    transformMatrix.resize(signalMatrix.rows(), signalMatrix.cols());

    m_fft.inverseTransform(transformMatrix, inverseTransformMatrix);

    m_filteredImage.load(inverseTransformMatrix, m_baseImage.pixmap().width(), m_baseImage.pixmap().height());
    ui->filteredImageLabel->setPixmap(m_filteredImage.pixmap());

    ////////////////////////////////////////////////////////////////////////////////////
}

void MainWindow::updateTransformView(const ComplexMatrix& transformMatrix)
{
    int r;
    int c;
    int rowCount;
    int colCount;

    rowCount = transformMatrix.rows();
    colCount = transformMatrix.cols();

    QImage transformImage(colCount, rowCount, QImage::Format_RGB32);

    for (r = 0; r < rowCount; ++r)
    {
        for (c = 0; c < colCount; ++c)
        {
            if (fabs(transformMatrix.at(r, c).real()) > 0.01f)
                transformImage.setPixel(c, r, qRgb(255, 255, 255));
            else
                transformImage.setPixel(c, r, qRgb(0, 0, 0));
        }
    }

    m_transformPixmap = QPixmap::fromImage(transformImage).scaled(m_baseImage.pixmap().size());
    ui->transformImageLabel->setPixmap(m_transformPixmap);

//    QLabel* label = new QLabel();
//    label->setPixmap(m_transformPixmap);
//    label->setGraphicsEffect(new QGraphicsEffect());

//    QPixmap output(inPixmap.width(), inPixmap.height());
//    QPainter painter(&output);
//    label->render(&painter);

//    delete label;
}
