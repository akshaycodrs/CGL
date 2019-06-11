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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    void solid(float,float,float,float);
    void dotted(float,float,float,float);
    void dash(float,float,float,float);
    void dashdot(float,float,float,float);
    void thick(float,float,float,float,float);
    int sign(float);
};

#endif // MAINWINDOW_H
