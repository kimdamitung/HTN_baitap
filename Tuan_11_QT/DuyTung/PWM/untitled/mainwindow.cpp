#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <QTimer>

#define PWM_IOCTL_SET_FREQ  1
#define PWM_IOCTL_STOP      0

int pwm_fd;
int freq = 1000;
bool state = true;
QTimer *timer_one = new QTimer();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(freq));
    ui->lineEdit->setStyleSheet("text-align: center; padding: 0 0 0 35px");
    ui->cong->setEnabled(false);
    ui->tru->setEnabled(false);
    connect(timer_one, SIGNAL(timeout()), this, SLOT(start_buzzer()));
    pwm_fd = open("/dev/pwm", 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_buzzer(){
    if(pwm_fd != -1)
        ioctl(pwm_fd, PWM_IOCTL_SET_FREQ, freq);
}

void MainWindow::on_cong_clicked()
{
    freq += 100;
    if(freq >= 2000)
        freq = 2000;
    ui->lineEdit->setText(QString::number(freq));
}

void MainWindow::on_tru_clicked()
{
    freq -= 100;
    if(freq <= 100)
        freq = 100;
    ui->lineEdit->setText(QString::number(freq));
}



void MainWindow::on_start_clicked()
{
    if(state == true){
        state = false;
        ui->start->setText("Stop");
        ui->cong->setEnabled(true);
        ui->tru->setEnabled(true);
        timer_one->start();
    }
    else if(state == false){
        state = true;
        ui->start->setText("Start");
        ui->cong->setEnabled(false);
        ui->tru->setEnabled(false);
        timer_one->stop();
        ioctl(pwm_fd, PWM_IOCTL_STOP);
    }
}

void MainWindow::on_close_clicked()
{
    close();
}
