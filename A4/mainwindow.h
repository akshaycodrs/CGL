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
    bool start;
    int j;
    int a[20],b[20];

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void dda(float,float,float,float);
    int sign(float);
    void mousePressEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
