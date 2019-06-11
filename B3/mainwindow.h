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

private:
    Ui::MainWindow *ui;
    int ver;
    int arrx[100];
    int arry[100];
    bool start;

    const int in = 0;               //0000
    const int left = 1;             //0001
    const int right = 2;           //0010
    const int bottom = 4;       //0100
    const int top = 8;             //1000

    //DIagonals of the Rectangle
    const int x_max = 250;
    const int y_max = 200;
    const int x_min = 100;
    const int y_min = 100;

    void dda(float,float,float,float);
    int codecheck(int , int );
    void CohenS(int, int, int, int);
    void mousePressEvent(QMouseEvent *);
    int sign(float);
};

#endif // MAINWINDOW_H
