#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Edge.h"
#include "EdgeView.h"
#include "FourierTransform.h"
#include "FourierLowPassFilter.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_fourierTransform(new FourierTransform()),
    m_lowPassFilter(new FourierLowPassFilter())
{
    ui->setupUi(this);

    initializeEdges();

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

void MainWindow::onEdgeViewMouseClicked(const QPoint &pos)
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

    m_fourierTransform->transform(m_baseEdge->points(), fourierValues);
    m_lowPassFilter->filter(fourierValues);
    m_fourierTransform->inverseTransform(fourierValues, edgePoints);
    m_filteredEdge->setPoints(edgePoints);
}
