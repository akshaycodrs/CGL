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

void MainWindow::solid(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
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

void MainWindow::dotted(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    float x,y,dx,dy,step,i=1;
    int count=0;
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
        if(count%2==0)
        {
            image.setPixel(x,y,value);
        }
        x=x+dx*sign(x2-x1);
        y=y+dy*sign(y2-y1);
        i++;
        count++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::dash(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
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
    int count=0;
    while(i<=step)
    {
        if(count%10!=0)
        {
            image.setPixel(x,y,value);
        }
        x=x+dx*sign(x2-x1);
        y=y+dy*sign(y2-y1);
        i++;
        count++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::dashdot(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    float dx,dy,x,y,i=1,step;
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
    int count=0;
    while(i<=step)
    {
        if(count%10<3 || count%10==6)
        {
            image.setPixel(x,y,value);
        }
        x=x+dx*sign(x2-x1);
        y=y+dy*sign(y2-y1);
        i++;
        count++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::thick(float x1,float y1,float x2,float y2,float w)
{
    QRgb value;
    value=qRgb(0,255,0);
    float dx,dy,x,y,step,i=1;
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
        if(x1==x2)
        {
            for(int i=0;i<=w;i++)
            {
                image.setPixel(x+i,y,value);
            }
        }
        else
        {
            for(int i=0;i<w;i++)
            {
                image.setPixel(x,y+i,value);
            }
        }
        x=x+dx*sign(x2-x1);
        y=y+dy*sign(y2-y1);
        i++;
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
    solid(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    dotted(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    dash(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    dashdot(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_5_clicked()
{
    float x1,y1,x2,y2,w;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    w=ui->textEdit_5->toPlainText().toFloat();
    thick(x1,y1,x2,y2,w);
}
