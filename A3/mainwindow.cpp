#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
QImage image(300, 300, QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DDA(0,150,300,150);
    DDA(150,0,150,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow:: sign(float p)
{
    if(p<0)
        return -1;
    else
        return 1;
}
void MainWindow :: DDA(float x1, float y1, float x2, float y2)
{
    float dx,dy,len,x,y;
    int i = 1;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(dx) > abs(dy))
    {
        len = abs(dx);
    }
    else
    {
        len = abs(dy);
    }
    dx = dx/len;
    dy = dy/len;
    x = x1 + 0.5*sign(x2-x1);
    y = y1 + 0.5*sign(y2-y1);
    while(i<=len)
    {
        image.setPixel(x,y, qRgb(255,255,255));
        x = x+dx;
        y = y+dy;
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::on_pushButton_clicked()
{
    float x1, y1, x2, y2, tx, ty;
      x1 = ui->textEdit -> toPlainText().toFloat();
      y1 = ui->textEdit_2->toPlainText().toFloat();
      x2 = ui->textEdit_3->toPlainText().toFloat();
      y2 = ui->textEdit_4->toPlainText().toFloat();
      tx = ui->textEdit_5->toPlainText().toFloat();
      ty = ui->textEdit_6 -> toPlainText().toFloat();
      trans(x1,y1,x2,y2,tx,ty);
}
void MainWindow :: trans(float x1, float y1, float x2, float y2, float tx, float ty)
{
   int c[2][3];
   int t[3][3];
   int final[2][3] = {0};
   c[0][0] = x1;
   c[0][1] = y1;
   c[1][0] = x2;
   c[1][1] = y2;
   c[0][2] = 1;
   c[1][2] = 1;
   t[0][1] = 0;
   t[0][2] = 0;
   t[1][0] = 0;
   t[1][2] = 0;
   t[0][0] = 1;
   t[1][1] = 1;
   t[2][2] = 1;
   t[2][0] = tx;
   t[2][1] = ty;
   for(int i=0;i<2;i++)
   {
       for(int j=0;j<3;j++)
       {
           final[i][j] = 0;
           for(int k=0;k<3;k++)
           {
               final[i][j] += c[i][k]*t[k][j];
           }
       }
   }
   DDA(final[0][0]+150, -final[0][1]+150, final[1][0]+150, -final[1][1]+150);
}
void MainWindow::on_pushButton_4_clicked()
{
    float x1,x2,y1,y2;
     x1 = ui->textEdit -> toPlainText().toFloat();
     y1 = ui->textEdit_2->toPlainText().toFloat();
     x2 = ui->textEdit_3->toPlainText().toFloat();
     y2 = ui->textEdit_4->toPlainText().toFloat();
     DDA(x1+150,-y1+150,x2+150,-y2+150);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1, y1, x2, y2, sx, sy;
      x1 = ui->textEdit -> toPlainText().toFloat();
      y1 = ui->textEdit_2->toPlainText().toFloat();
      x2 = ui->textEdit_3->toPlainText().toFloat();
      y2 = ui->textEdit_4->toPlainText().toFloat();
      sx = ui->textEdit_5->toPlainText().toFloat();
      sy = ui->textEdit_6 -> toPlainText().toFloat();
      scale(x1,y1,x2,y2,sx,sy);
}
void MainWindow :: scale(float x1, float y1, float x2, float y2, float sx, float sy)
{
   int c[2][3];
   int s[3][3];
   int final[2][3] = {0};
   c[0][0] = x1;
   c[0][1] = y1;
   c[1][0] = x2;
   c[1][1] = y2;
   c[0][2] = 1;
   c[1][2] = 1;
   s[0][1] = 0;
   s[0][2] = 0;
   s[1][0] = 0;
   s[1][2] = 0;
   s[0][0] = sx;
   s[1][1] = sy;
   s[2][2] = 1;
   s[2][0] = 0;
   s[2][1] = 0;
   for(int i=0;i<2;i++)
   {
       for(int j=0;j<3;j++)
       {
           final[i][j] = 0;
           for(int k=0;k<3;k++)
           {
               final[i][j] += c[i][k]*s[k][j];
           }
       }
   }
   DDA(final[0][0]+150, -final[0][1]+150, final[1][0]+150, -final[1][1]+150);
}
void MainWindow :: rotate(float x1, float y1, float x2, float y2, float t)
{
    float trans[3][3];
    float cor[2][3];
    float res[2][3];

    float th;
    th=(3.14*t)/180;

    trans[0][0]=cos(th);
    trans[0][1]=-sin(th);
    trans[0][2]=0;
    trans[1][0]=sin(th);
    trans[1][1]=cos(th);
    trans[1][2]=0;
    trans[2][0]=0;
    trans[2][1]=0;
    trans[2][2]=1;

    cor[0][0]=x1;
    cor[0][1]=y1;
    cor[0][2]=1;
    cor[1][0]=x2;
    cor[1][1]=y2;
    cor[1][2]=1;


    for(int m=0;m<2;m++)
    {
        for(int n=0;n<3;n++)
        {
            res[m][n]=0;
        }
    }

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {

            for(int k=0;k<3;k++)
                res[i][j]=res[i][j]+cor[i][k]*trans[k][j];
        }
    }

    DDA(res[0][0]+150,-res[0][1]+150,res[1][0]+150,-res[1][1]+150);
}
void MainWindow::on_pushButton_3_clicked()
{
    float x1, y1, x2, y2,t;
      x1 = ui->textEdit -> toPlainText().toFloat();
      y1 = ui->textEdit_2->toPlainText().toFloat();
      x2 = ui->textEdit_3->toPlainText().toFloat();
      y2 = ui->textEdit_4->toPlainText().toFloat();
      t = ui->textEdit_7->toPlainText().toFloat();
      rotate(x1,y1,x2,y2,t);
}
