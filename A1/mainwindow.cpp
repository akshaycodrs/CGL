#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(300,300,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    dda(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    bresenham(x1,y1,x2,y2);
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    float dx,dy,x,y,i,step;
    i=1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    if(dx>=dy)
    {
        step=dx;
    }
    else
    {
        step=dy;
    }
    dx=dx/step;
    dy=dy/step;
    x=x1;
    y=y1;
    while(i<=step)
    {
        image.setPixel(x,y,value);
        x=x+dx*sign(x2-x1);
        y=y+dy*sign(y2-y1);
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
int MainWindow::sign(float a)
{
    if(a>0)
        return 1;
    else
        return -1;
}

void MainWindow::bresenham(int x1,int y1,int x2,int y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    int dx,dy,x,y,p,i=0;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    x=x1;
    y=y1;
    if(dx>=dy)
    {
        p=2*dy-dx;
        while(i<dx)
        {
            image.setPixel(x,y,value);
            x=x+sign(x2-x1);
            if(p<0)
            {
                p=p+2*dy;
            }
            else
            {
                p=p+2*(dy-dx);
                y=y+sign(y2-y1);
            }
            i++;
        }
    }
    else
    {
        p=2*dx-dy;
        while(i<dy)
        {
            image.setPixel(x,y,value);
            y=y+sign(y2-y1);
            if(p<0)
            {
                p=p+2*dx;
            }
            else
            {
                p=p+2*(dx-dy);
                x=x+sign(x2-x1);
            }
            i++;
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
