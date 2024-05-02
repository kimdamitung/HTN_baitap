#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

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
    //infor
    QMessageBox::information(this,"Title here","Text here");
}

void MainWindow::on_pushButton_2_clicked()
{
    //question
    QMessageBox::question(this,"Title here","Do you like cats",QMessageBox::Yes|QMessageBox::No);
}
