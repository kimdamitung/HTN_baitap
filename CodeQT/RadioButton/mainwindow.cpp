#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
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
    if (ui->radioButton1->isChecked())
        QMessageBox::information(this,"Title",ui->radioButton1->text());
    else
        QMessageBox::information(this,"Title",ui->radioButton2->text());

}
