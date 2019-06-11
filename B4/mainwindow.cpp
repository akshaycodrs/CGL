#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "math.h"

QImage image(300,300,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dda(0,150,300,150);
    dda(150,0,150,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(0,255,0);
    float dx,dy,step,x,y,i=1;
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


void MainWindow::refx(float x1,float y1,float x2,float y2)
{
    float a[2][3],b[2][3],c[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                c[i][i]=1;
            }
            else
            {
                c[i][j]=0;
            }
        }
    }
    c[0][0]=1;
    c[1][1]=-1;
    b[0][0]=x1;
    b[0][1]=y1;
    b[0][2]=1;
    b[1][0]=x2;
    b[1][1]=y2;
    b[1][2]=1;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            a[i][j]=0;
        }
    }
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                a[i][j]=a[i][j]+b[i][k]*c[k][j];
            }
        }
    }
    dda(a[0][0]+150,-a[0][1]+150,a[1][0]+150,-a[1][1]+150);
}

void MainWindow::refy(float x1,float y1,float x2,float y2)
{
    float a[2][3],b[2][3],c[3][3];
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            a[i][j]=0;
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                c[i][j]=1;
            }
            else
            {
                c[i][j]=0;
            }
        }
    }
    c[0][0]=-1;
    c[1][1]=1;
    b[0][0]=x1;
    b[0][1]=y1;
    b[0][2]=1;
    b[1][0]=x2;
    b[1][1]=y2;
    b[1][2]=1;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                a[i][j]=a[i][j]+b[i][k]*c[k][j];
            }
        }
    }
    dda(a[0][0]+150,-a[0][1]+150,a[1][0]+150,-a[1][1]+150);
}

void MainWindow::refxy(float x1,float y1,float x2,float y2)
{
    int a[2][3],b[2][3],c[3][3];
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            a[i][j]=0;
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                c[i][i]=1;
            }
            else
            {
                c[i][j]=0;
            }
        }
    }
    c[0][0]=0;
    c[0][1]=1;
    c[1][0]=1;
    c[1][1]=0;
    b[0][0]=x1;
    b[0][1]=y1;
    b[0][2]=1;
    b[1][0]=x2;
    b[1][1]=y2;
    b[1][2]=1;

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                a[i][j]=a[i][j]+b[i][k]*c[k][j];
            }
        }
    }
    dda(a[0][0]+150,-a[0][1]+150,a[1][0]+150,-a[1][1]+150);
}

void MainWindow::rotate(float x1,float y1,float x2,float y2,float ax,float ay,float theta)
{
    float arbi[3][3];float rota[3][3];float arbic[3][3];float ini[3][3],fin[2][3],comp[3][3],a[2][3];
       a[0][0]=x1;
       a[0][1]=y1;
       a[1][0]=x2;
       a[1][1]=y2;
       a[0][2]=1;
       a[1][2]=1;
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               if(i==j)
               {
                   arbi[i][i]=1;
               }
               else
               {
                  arbi[i][j]=0;
               }
           }
       }
       arbi[2][0]=-ax;
       arbi[2][1]=-ay;
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               if(i==j)
               {
                   arbic[i][i]=1;
               }
               else
               {
                  arbic[i][j]=0;
               }
           }
       }
       arbic[2][0]=ax;
       arbic[2][1]=ay;
       theta=(3.14/180)*theta;
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               if(i==j)
               {
                   rota[i][i]=1;
               }
               else
               {
                   rota[i][j]=0;
               }
           }
       }
       rota[0][0]=cos(theta);
       rota[0][1]=-sin(theta);
       rota[1][0]=sin(theta);
       rota[1][1]=cos(theta);

       int k=0;
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               ini[i][j]=0;
           }
       }
       for(int i=0;i<2;i++)
       {
           for(int j=0;j<3;j++)
           {
               fin[i][j]=0;
           }
       }
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               comp[i][j]=0;
           }
       }
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               for(k=0;k<3;k++)
               {
                    ini[i][j]=ini[i][j]+arbi[i][k]*rota[k][j];
               }
           }
       }
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               for(k=0;k<3;k++)
               {
                    comp[i][j]=comp[i][j]+ini[i][k]*arbic[k][j];
               }
           }
       }
       for(int i=0;i<2;i++)
       {
           for(int j=0;j<3;j++)
           {
               for(k=0;k<3;k++)
               {
                    fin[i][j]=fin[i][j]+a[i][k]*comp[k][j];
               }
           }
       }
         dda(fin[0][0]+150,-fin[0][1]+150,fin[1][0]+150,-fin[1][1]+150);

}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    refx(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    refy(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    refxy(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2,ax,ay,theta;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    ax=ui->textEdit_5->toPlainText().toFloat();
    ay=ui->textEdit_6->toPlainText().toFloat();
    theta=ui->textEdit_7->toPlainText().toFloat();
    rotate(x1,y1,x2,y2,ax,ay,theta);
}

void MainWindow::on_pushButton_5_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    dda(x1+150,-y1+150,x2+150,-y2+150);
}
