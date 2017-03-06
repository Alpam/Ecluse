#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_boutonModeAuto_released();

    void on_boutonModeExp_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
