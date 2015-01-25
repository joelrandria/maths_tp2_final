#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Image.h"
#include "FastFourierTransform.h"

namespace Ui {
class MainWindow;
}

class Fourier2DFilter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

    Image m_baseImage;
    Image m_filteredImage;

    FastFourierTransform m_fft;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOpen_triggered();
    void on_actionQuit_triggered();

    void onBaseImageChanged(Image*);
    void onFilteredSpectrumChanged(Fourier2DFilter*);
};

#endif // MAINWINDOW_H
