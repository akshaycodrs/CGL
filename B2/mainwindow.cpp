#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMouseEvent>
QImage image(300,300,QImage::Format_RGB888);
QColor col,bg;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
    start=true;
    j=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=col.rgb();
    float x,y,dx,dy,step,i=1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    if(dx>=dy)
        step=dx;
    else
        step=dy;
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
    if(start==true)
    {
        int p=ev->pos().x();
        int q=ev->pos().y();
        a[j]=p;
        b[j]=q;
        if(ev->button()==Qt::RightButton)
        {
            dda(a[0],b[0],a[j-1],b[j-1]);
            start=false;
        }
        else
        {
            if(j>0)
            {
                dda(a[j-1],b[j-1],a[j],b[j]);
            }
            j++;
        }
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int p=ev->pos().x();
    int q=ev->pos().y();

    bg=image.pixel(p,q);
    seedfill(p,q);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::seedfill(int x, int y)
{
    QRgb curr=image.pixel(x,y);
    if(curr==bg.rgb())
    {
        image.setPixel(x,y,col.rgb());
        seedfill(x+1,y);
        seedfill(x,y+1);
        seedfill(x-1,y);
        seedfill(x,y-1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    col=QColorDialog::getColor();
}
