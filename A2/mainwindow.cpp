#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
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


void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    float x,y,dx,dy,step,i;
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
    i=1;
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
    if(a<0)
        return -1;
    else
        return 1;
}


void MainWindow::DDACircle(float c1,float c2,float r)
{
    QRgb value;
    value=qRgb(0,255,0);
    float x,y,sx,sy,eps;
    x=r;
    y=0;
    sx=x;
    sy=y;
    do
    {
        val=pow(2,i);
        i++;
    }while(val<r);
    eps=1/pow(2,i-1);
    do
    {
        x1=x+y*eps;
        y1=y-x1*eps;
        image.setPixel(c1+x1,c2-y1,value);
        x=x1;
        y=y1;
    }while((sx-x)>eps || (y-sy)<eps);

    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::BCircle(int c1,int c2,int r)
{
    int x,y,d;
    x=0;
    y=r;
    d=3-2*r;
    while(x<=y)
    {
        image.setPixel(c1+x,c2+y,value);
        image.setPixel(c1+x,c2-y,value);
        image.setPixel(c1-x,c2+y,value);
        image.setPixel(c1-x,c2-y,value);
        image.setPixel(c1+y,c2+x,value);
        image.setPixel(c1+y,c2-x,value);
        image.setPixel(c1-y,c2+x,value);
        image.setPixel(c1-y,c2-x,value);
        if(d<0)
        {
            d=d+4*x+6;
        }
        else
        {
            d=d+(4*(x-y))+10;
            y--;
        }
        x++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

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
    float c1,c2,r;
    c1=ui->textEdit_6->toPlainText().toFloat();
    c2=ui->textEdit_7->toPlainText().toFloat();
    r=ui->textEdit_5->toPlainText().toFloat();
    DDACircle(c1,c2,r);
}

void MainWindow::on_pushButton_3_clicked()
{
    int c1,c2,r;
    c1=ui->textEdit_6->toPlainText().toInt();
    c2=ui->textEdit_7->toPlainText().toInt();
    r=ui->textEdit_5->toPlainText().toInt();
    BCircle(c1,c2,r);
}
