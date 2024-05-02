#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QTimer>

QTimer *timer = new QTimer();
int scan_key();
int buttons_fd;
char buttons[6] = {'0', '0', '0', '0', '0', '0'};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inital_setup();
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::process(){
    int k;
    k = scan_key();
    switch(k){
    case 10:
        MainWindow::ui->btnK1->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
    case 20:
        MainWindow::ui->btnK2->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
    case 30:
        MainWindow::ui->btnK3->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
    case 40:
        MainWindow::ui->btnK4->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
    case 50:
        MainWindow::ui->btnK5->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
    case 60:
        MainWindow::ui->btnK6->setStyleSheet("background-color: blue; font: bold 26px;");
        break;
//    case 70:
//        MainWindow::ui->btnK7->setStyleSheet("background-color: blue; font: bold 26px;");
//        break;
//    case 80:
//        MainWindow::ui->btnK8->setStyleSheet("background-color: blue; font: bold 26px;");
//        break;
    case 11:
        MainWindow::ui->btnK1->setStyleSheet("background-color: red; font: bold 26px;");
        break;
    case 21:
        MainWindow::ui->btnK2->setStyleSheet("background-color: red; font: bold 26px;");
        break;
    case 31:
        MainWindow::ui->btnK3->setStyleSheet("background-color: red; font: bold 26px;");
        break;
    case 41:
        MainWindow::ui->btnK4->setStyleSheet("background-color: red; font: bold 26px;");
        break;
    case 51:
        MainWindow::ui->btnK5->setStyleSheet("background-color: red; font: bold 26px;");
        break;
    case 61:
        MainWindow::ui->btnK6->setStyleSheet("background-color: red; font: bold 26px;");
        break;
//    case 71:
//        MainWindow::ui->btnK7->setStyleSheet("background-color: red; font: bold 26px;");
//        break;
//    case 81:
//        MainWindow::ui->btnK8->setStyleSheet("background-color: red; font: bold 26px;");
//        break;
    }
}

void MainWindow::inital_setup(){
    MainWindow::ui->btnK1->setStyleSheet("background-color: blue; font: bold 26px;");
    MainWindow::ui->btnK2->setStyleSheet("background-color: blue; font: bold 26px;");
    MainWindow::ui->btnK3->setStyleSheet("background-color: blue; font: bold 26px;");
    MainWindow::ui->btnK4->setStyleSheet("background-color: blue; font: bold 26px;");
    MainWindow::ui->btnK5->setStyleSheet("background-color: blue; font: bold 26px;");
    MainWindow::ui->btnK6->setStyleSheet("background-color: blue; font: bold 26px;");
//    MainWindow::ui->btnK7->setStyleSheet("background-color: blue; font: bold 26px;");
//    MainWindow::ui->btnK8->setStyleSheet("background-color: blue; font: bold 26px;");
    do{
        buttons_fd = open("/dev/buttons", 0);
    }while(buttons_fd < 0);
}

int scan_key(){
    int i;
    char current_buttons[6];
    if(read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons)
        return 0;
    for(i = 0; i < 6; i++){
        if(buttons[i] != current_buttons[i]){
            buttons[i] = current_buttons[i];
            if(buttons[i] == '1'){
                return ((10 * (i + 1)) + 1);
            }else{
                return (10 * (i + 1));
            }
        }
    }
    return 0;
}
