#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EdgeBuilder.h"

namespace Ui {
class MainWindow;
}

class Edge;
class IFourierTransform;
class FourierLowPassFilter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

    EdgeBuilder m_edgeBuilder;

    Edge* m_baseEdge;
    Edge* m_filteredEdge;

    IFourierTransform* m_fourierTransform;
    IFourierTransform* m_fastFourierTransform;

    FourierLowPassFilter* m_lowPassFilter;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void initializeEdges();

    void updateBaseEdgeInfos();
    void updateFilteredEdge();

private slots:

    void on_actionCloseApplication_triggered();
    void on_actionNewEdge_triggered();

    void onEdgeViewMouseClicked(const QPoint& pos);
    void onBaseEdgePointsChanged(Edge*);

    void on_lowPassFilterSlider_valueChanged(int value);
    void on_lowPassFilterSpinbox_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
