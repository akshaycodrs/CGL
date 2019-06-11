#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<QtDebug>
#include <QColorDialog>
QImage image(400,400,QImage::Format_RGB888);
QRgb value=qRgb(0,255,0);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float dx,dy,x,y,step,i=1;
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
    if(a<0)
        return -1;
    else
        return 1;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    int p=ev->pos().x();
    int q=ev->pos().y();
    arrx[ver]=p;
    arry[ver]=q;
    ver++;
    if(ver%2==0)
    {
        CohenS(arrx[ver-1],arry[ver-1],arrx[ver-2],arry[ver-2]);
    }
}

int MainWindow::codecheck(int x,int y)
{
    int code=in;
    if(x<x_min)
        code|=left;
    else if(x>x_max)
        code|=right;
    if(y<y_min)
        code|=bottom;
    else if(y>y_max)
        code|=top;

    return code;
}

void MainWindow::CohenS(int x1,int y1,int x2,int y2)
{
    int code1=codecheck(x1,y1);
    int code2=codecheck(x2,y2);
    bool accept=false;
    while(true)
    {
        if((code1==0) && (code2==0))
        {
            accept=true;
            break;
        }
        else if(code1 & code2)
        {
            break;
        }
        else
        {
            int outcode;
            double x,y;
            if(code1!=0)
            {
                outcode=code1;
            }
            else
            {
                outcode=code2;
            }
            if(outcode & top)
            {
                x=x1+(x2-x1)*(y_max-y1)/(y2-y1);
                y=y_max;
            }
            else if(outcode & bottom)
            {
                x=x1+(x2-x1)*(y_min-y1)/(y2-y1);
                y=y_min;
            }
            else if(outcode & left)
            {
                y=y1+(y2-y1)*(x_min-x1)/(x2-x1);
                x=x_min;
            }
            else if(outcode & right)
            {
                y=y1+(y2-y1)*(x_max-x1)/(x2-x1);
                x=x_max;
            }

            if(outcode==code1)
            {
                x1=x;
                y1=y;
                code1=codecheck(x,y);
            }
            else
            {
                x2=x;
                y2=y;
                code2=codecheck(x,y);
            }
        }
    }
    if(accept)
    {
        dda(x1,y1,x2,y2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    dda(100, 100, 250, 100);
    dda(250, 100, 250, 200);
    dda(250, 200, 100, 200);
    dda(100, 200, 100, 100);
}
