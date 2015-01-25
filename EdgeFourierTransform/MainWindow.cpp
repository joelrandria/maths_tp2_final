#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Edge.h"
#include "EdgeView.h"
#include "FourierTransform.h"
#include "FastFourierTransform.h"
#include "FourierLowPassFilter.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_fourierTransform(new FourierTransform()),
    m_fastFourierTransform(new FastFourierTransform()),
    m_lowPassFilter(new FourierLowPassFilter())
{
    ui->setupUi(this);

    initializeEdges();

    connect(ui->edgeView, SIGNAL(mouseClicked(const QPoint&)), this, SLOT(onEdgeViewMouseClicked(const QPoint&)));

    //////////////////////////////////////////////////////////////////////////

//    ComplexVector spaceValues;
//    ComplexVector spectralValues;
//    ComplexVector inverseValues;

//    spaceValues.push_back(Complex(0, 0));
//    spaceValues.push_back(Complex(50, 50));
//    spaceValues.push_back(Complex(100, 100));
//    spaceValues.push_back(Complex(150, 150));
//    spaceValues.push_back(Complex(200, 200));
//    spaceValues.push_back(Complex(250, 250));
//    spaceValues.push_back(Complex(300, 300));
//    spaceValues.push_back(Complex(350, 350));
//    spaceValues.push_back(Complex(400, 400));
//    spaceValues.push_back(Complex(450, 450));
//    spaceValues.push_back(Complex(500, 500));
//    spaceValues.push_back(Complex(550, 550));
//    spaceValues.push_back(Complex(600, 600));
//    spaceValues.push_back(Complex(650, 650));
//    spaceValues.push_back(Complex(700, 700));
//    spaceValues.push_back(Complex(750, 750));

//    spectralValues.resize(spaceValues.size());
//    inverseValues.resize(spaceValues.size());

//    // FT
//    m_fourierTransform->transform(spaceValues, spectralValues);
//    FastFourierTransform::printValues("----- Transformée de Fourier lente -----", spectralValues);
//    m_fourierTransform->inverseTransform(spectralValues, inverseValues);

//    m_baseEdge->setPoints(spaceValues);
//    m_filteredEdge->setPoints(inverseValues);

//    // FFT
//    m_fastFourierTransform->transform(spaceValues, spectralValues);
//    FastFourierTransform::printValues("----- Transformée de Fourier rapide -----", spectralValues);
//    m_fourierTransform->inverseTransform(spectralValues, inverseValues);

//    m_baseEdge->setPoints(spaceValues);
//    m_filteredEdge->setPoints(inverseValues);
}
MainWindow::~MainWindow()
{
    delete ui;

    delete m_baseEdge;
    delete m_filteredEdge;
}

void MainWindow::initializeEdges()
{
    m_baseEdge = new Edge(Qt::blue);
    connect(m_baseEdge, SIGNAL(pointsChanged(Edge*)), this, SLOT(onBaseEdgePointsChanged(Edge*)));
    ui->edgeView->addEdge(m_baseEdge);

    m_filteredEdge = new Edge(Qt::red);
    ui->edgeView->addEdge(m_filteredEdge);
}

void MainWindow::on_actionCloseApplication_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNewEdge_triggered()
{
    m_baseEdge->clear();
    m_filteredEdge->clear();

    m_edgeBuilder.clear();

    ui->lowPassFilterSpinbox->setValue(0);
}

void MainWindow::onEdgeViewMouseClicked(const QPoint& pos)
{
    ComplexVector baseEdgePoints;

    m_edgeBuilder.addVertex(Complex(pos.x(), pos.y()));
    m_edgeBuilder.getEdgePoints(baseEdgePoints);

    m_baseEdge->setPoints(baseEdgePoints);
}

void MainWindow::onBaseEdgePointsChanged(Edge *)
{
    updateBaseEdgeInfos();
    updateFilteredEdge();
}

void MainWindow::on_lowPassFilterSlider_valueChanged(int value)
{
    ui->lowPassFilterSpinbox->setValue(value);
}
void MainWindow::on_lowPassFilterSpinbox_valueChanged(double arg1)
{
    ui->lowPassFilterSlider->setValue(arg1);

    m_lowPassFilter->setThreshold(arg1);

    updateFilteredEdge();
}

void MainWindow::updateBaseEdgeInfos()
{
    uint edgePointCount;

    if (ui->edgeView->edgeCount() > 0)
        edgePointCount = ui->edgeView->edge(0)->points().size();
    else
        edgePointCount = 0;

    ui->edgePointCountLabel->setText(QString("%1").arg(edgePointCount));
}

void MainWindow::updateFilteredEdge()
{
    uint valueCount;

    ComplexVector edgePoints;
    ComplexVector fourierValues;

    valueCount = m_baseEdge->points().size();

    edgePoints.resize(valueCount);
    fourierValues.resize(valueCount);

    //m_fourierTransform->transform(m_baseEdge->points(), fourierValues);
    m_fastFourierTransform->transform(m_baseEdge->points(), fourierValues);
    m_lowPassFilter->filter(fourierValues);
    m_fourierTransform->inverseTransform(fourierValues, edgePoints);
    m_filteredEdge->setPoints(edgePoints);
}
