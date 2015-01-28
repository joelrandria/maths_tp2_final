#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Image.h"
#include "Fourier2DFilter.h"
#include "FastFourierTransform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow* ui;

    Image m_baseImage;
    Image m_filteredImage;

    FastFourierTransform m_fft;

    Fourier2DFilter m_spectrumFilter;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionShowSpectrumFilter_triggered();

    void on_fitPicturesToWindowCheckBox_clicked(bool checked);

    void onBaseImageChanged(Image*);
    void onFilteredSpectrumChanged(Fourier2DFilter*, ComplexMatrix&);

protected:

    void resizeEvent(QResizeEvent* event);

private:

    void updatePictureViewLayouts();

};

#endif // MAINWINDOW_H
