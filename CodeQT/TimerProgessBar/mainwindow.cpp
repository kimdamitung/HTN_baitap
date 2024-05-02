#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
QTimer *timer1=new QTimer();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(increment()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::increment()
{
    val=ui->progressBar->value();
    val++;
    ui->progressBar->setValue(val);

}

void MainWindow::on_pushButton_clicked()

{
    if(timer1->isActive())
    {
        timer1->stop();
        ui->pushButton->setText("Run");
    }
    else
    {
        timer1->start(100);

        ui->pushButton->setText("Pause");

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    timer1->stop();
    ui->pushButton->setText("Run");
    val=0;
    ui->progressBar->setValue(val);
}
