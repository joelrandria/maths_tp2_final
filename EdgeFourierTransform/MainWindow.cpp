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
    m_lowPassFilter(new FourierLowPassFilter())
{
    ui->setupUi(this);
    ui->progressBar->hide();

    initializeEdges();
    initializeFourierTransforms();

    connect(ui->edgeView, SIGNAL(mouseClicked(const QPoint&)), this, SLOT(onEdgeViewMouseClicked(const QPoint&)));
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
void MainWindow::initializeFourierTransforms()
{
    m_fourierTransforms[0] = new FourierTransform();
    m_fourierTransforms[1] = new FastFourierTransform();
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
    int selectedTransform;

    ComplexVector edgePoints;
    ComplexVector fourierValues;

    valueCount = m_baseEdge->points().size();

    selectedTransform = ui->methodTypeComboBox->currentIndex();

    edgePoints.resize(valueCount);
    fourierValues.resize(valueCount);

    ui->progressBar->show();

    m_timer.restart();
    m_fourierTransforms[selectedTransform]->transform(m_baseEdge->points(), fourierValues);
    ui->transformTimeLabel->setText(QString("%1").arg((float)m_timer.elapsed() / 1000));

    m_lowPassFilter->filter(fourierValues);

    m_timer.restart();
    m_fourierTransforms[selectedTransform]->inverseTransform(fourierValues, edgePoints);
    ui->inverseTransformTimeLabel->setText(QString("%1").arg((float)m_timer.elapsed() / 1000));

    m_filteredEdge->setPoints(edgePoints);
}

void MainWindow::on_methodTypeComboBox_currentIndexChanged(int)
{
    updateFilteredEdge();

    ui->progressBar->hide();
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
