#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include "QMouseEvent"
#include<QDebug>

QImage image(400,400,QImage::Format_RGB888);
QRgb col=qRgb(255,255,255);
QRgb col1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{
    for(int i=0;i<400;i++)
    {
        for(int j=0;j<400;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int p=ev->pos().x();
    int q=ev->pos().y();

    col1=image.pixel(p,q);

    seedfill(p,q,col);


}

void MainWindow::Bresen(float x1,float y1,float x2,float y2)
{

    QRgb value;
    value=qRgb(255,255,255);
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int x=x1;
    int y=y1;
    int i=0;
    int p;

    if(dx>=dy)
    {
         p=2*dy-dx;


        while(i<dx)
        {
           image.setPixel(x,y,value);
           x=x+1*sign(x2,x1);

           if(p<0)
           {
               p=p+2*dy;
           }
           else{
             p=p+2*(dy-dx);
             y=y+1*sign(y2,y1);
           }
           i++;
        }
    }
    else{
         p=2*dx-dy;


        while(i<dy)
        {
           image.setPixel(x,y,value);
           y=y+1*sign(y2,y1);

           if(p<0)
           {
               p=p+2*dx;
           }
           else{
             p=p+2*(dx-dy);
             x=x+1*sign(x2,x1);
           }
           i++;
        }
    }
    image.setPixel(x,y,value);
     ui->label->setPixmap(QPixmap::fromImage(image));
}

int MainWindow::sign(float a,float b)
{
    if(a-b>=0)
        return 1;
    else
        return -1;
}



void MainWindow::seedfill(int x,int y,QRgb col)
{
    QRgb curr=image.pixel(x,y);
    if(curr==col1)
    {
        image.setPixel(x,y,col);
        seedfill(x,y+1,col);
        seedfill(x-1,y,col);
        seedfill(x,y-1,col);
        seedfill(x+1,y,col);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::drawchess()
{
    int x1[10]={100,100,100,300,150,200,250,100,100,100};
    int y1[10]={100,100,300,100,100,100,100,150,200,250};
    int x2[10]={300,100,300,300,150,200,250,300,300,300};
    int y2[10]={100,300,300,300,300,300,300,150,200,250};

    int sx[8]={155,255,105,205,155,255,105,205};
    int sy[8]={105,105,155,155,205,205,255,255};

    for(int i=0;i<10;i++)
    {
        Bresen(x1[i],y1[i],x2[i],y2[i]);
    }


}

void MainWindow::rotate()
{
    int x1[10]={100,100,100,300,150,200,250,100,100,100};
    int y1[10]={100,100,300,100,100,100,100,150,200,250};
    int x2[10]={300,100,300,300,150,200,250,300,300,300};
    int y2[10]={100,300,300,300,300,300,300,150,200,250};

    int sx[8]={155,255,105,205,155,255,105,205};
    int sy[8]={105,105,155,155,205,205,255,255};

    float rx1[10],rx2[10],ry1[10],ry2[10];

    for(int i=0;i<10;i++)
    {
        rx1[i]=((x1[i]-200)-(y1[i]-200))/sqrt(2);
        rx1[i]+=200;
        rx2[i]=((x2[i]-200)-(y2[i]-200))/sqrt(2);
        rx2[i]+=200;
        ry1[i]=((x1[i]-200)+(y1[i]-200))/sqrt(2);
        ry1[i]+=200;
        ry2[i]=((x2[i]-200)+(y2[i]-200))/sqrt(2);
        ry2[i]+=200;
    }
    for(int i=0;i<10;i++)
    {
        Bresen(rx1[i],ry1[i],rx2[i],ry2[i]);
    }

}

void MainWindow::on_pushButton_clicked()
{
    clear();
    drawchess();
}



void MainWindow::on_pushButton_2_clicked()
{
    clear();
    rotate();
}
