#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

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

    QElapsedTimer m_timer;

    EdgeBuilder m_edgeBuilder;

    Edge* m_baseEdge;
    Edge* m_filteredEdge;

    IFourierTransform* m_fourierTransforms[2];

    FourierLowPassFilter* m_lowPassFilter;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void initializeEdges();
    void initializeFourierTransforms();

    void updateBaseEdgeInfos();
    void updateFilteredEdge();

private slots:

    void on_actionCloseApplication_triggered();
    void on_actionNewEdge_triggered();

    void onEdgeViewMouseClicked(const QPoint& pos);
    void onBaseEdgePointsChanged(Edge*);

    void on_methodTypeComboBox_currentIndexChanged(int index);

    void on_lowPassFilterSlider_valueChanged(int value);
    void on_lowPassFilterSpinbox_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
