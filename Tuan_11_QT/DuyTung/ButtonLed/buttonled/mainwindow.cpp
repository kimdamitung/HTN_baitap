#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <QTimer>

#define ON  1
#define OFF 0

QTimer *timer = new QTimer();
bool statebtn0 = true;
bool statebtn1 = true;
bool statebtn2 = true;
bool statebtn3 = true;
int button_fd, led_fd;
char buttons[4] = {'0', '0', '0', '0'};
int ActivePushButtonAndButton();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn0->setStyleSheet("background-color: #00CC00;");
    ui->btn1->setStyleSheet("background-color: #00CC00;");
    ui->btn2->setStyleSheet("background-color: #00CC00;");
    ui->btn3->setStyleSheet("background-color: #00CC00;");
    ui->led0->setStyleSheet("border-radius: 25px; background-color: #555555;");
    ui->led1->setStyleSheet("border-radius: 25px; background-color: #555555;");
    ui->led2->setStyleSheet("border-radius: 25px; background-color: #555555;");
    ui->led3->setStyleSheet("border-radius: 25px; background-color: #555555;");
    led_fd = open("/dev/leds", 0);
    button_fd = open("/dev/buttons", 0);
    connect(timer, SIGNAL(timeout()), this, SLOT(xuly_button()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::xuly_button(){
    int key;
    key = ActivePushButtonAndButton();
    if(key == 11 && statebtn0 == true){
        ui->btn0->setStyleSheet("background-color: #339999;");
        ui->led0->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 0);
        statebtn0 = false;
    }else if(key == 11 && statebtn0 == false){
        ui->btn0->setStyleSheet("background-color: #00CC00;");
        ui->led0->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 0);
        statebtn0 = true;
    }else if(key == 21 && statebtn1 == true){
        ui->btn1->setStyleSheet("background-color: #339999;");
        ui->led1->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 1);
        statebtn1 = false;
    }else if(key == 21 && statebtn1 == false){
        ui->btn1->setStyleSheet("background-color: #00CC00;");
        ui->led1->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 1);
        statebtn1 = true;
    }else if(key == 31 && statebtn2 == true){
        ui->btn2->setStyleSheet("background-color: #339999;");
        ui->led2->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 2);
        statebtn2 = false;
    }else if(key == 31 && statebtn2 == false){
        ui->btn2->setStyleSheet("background-color: #00CC00;");
        ui->led2->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 2);
        statebtn2 = true;
    }else if(key == 41 && statebtn3 == true){
        ui->btn3->setStyleSheet("background-color: #339999;");
        ui->led3->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 3);
        statebtn3 = false;
    }else if(key == 41 && statebtn3 == false){
        ui->btn3->setStyleSheet("background-color: #00CC00;");
        ui->led3->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 3);
        statebtn3 = true;
    }
}

int ActivePushButtonAndButton(){
    int i;
    char cur_btn[4];
    if(read(button_fd, cur_btn, sizeof(cur_btn)) != sizeof(cur_btn))
        return 0;
    for(i = 0; i < 4; i++){
        if(buttons[i] != cur_btn[i]){
            buttons[i] = cur_btn[i];
            if(buttons[i] == '1')
               return (10 * (i + 1) + 1);
            else
                return (10 * (i + 1));
        }
    }
    return 0;
}

void MainWindow::on_btn0_clicked()
{
    if(statebtn0 == true){
        ui->btn0->setStyleSheet("background-color: #339999;");
        ui->led0->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 0);
        statebtn0 = false;
    }else if(statebtn0 == false){
        ui->btn0->setStyleSheet("background-color: #00CC00;");
        ui->led0->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 0);
        statebtn0 = true;
    }
}

void MainWindow::on_btn1_clicked()
{
    if(statebtn1 == true){
        ui->btn1->setStyleSheet("background-color: #339999;");
        ui->led1->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON ,1);
        statebtn1 = false;
    }else if(statebtn1 == false){
        ui->btn1->setStyleSheet("background-color: #00CC00;");
        ui->led1->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 1);
        statebtn1 = true;
    }
}

void MainWindow::on_btn2_clicked()
{
    if(statebtn2 == true){
        ui->btn2->setStyleSheet("background-color: #339999;");
        ui->led2->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 2);
        statebtn2 = false;
    }else if(statebtn2 == false){
        ui->btn2->setStyleSheet("background-color: #00CC00;");
        ui->led2->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 2);
        statebtn2 = true;
    }
}

void MainWindow::on_btn3_clicked()
{
    if(statebtn3 == true){
        ui->btn3->setStyleSheet("background-color: #339999;");
        ui->led3->setStyleSheet("background-color: #FFFF00; border-radius: 25px;");
        ioctl(led_fd, ON, 3);
        statebtn3 = false;
    }else if(statebtn3 == false){
        ui->btn3->setStyleSheet("background-color: #00CC00;");
        ui->led3->setStyleSheet("background-color: #555555; border-radius: 25px;");
        ioctl(led_fd, OFF, 3);
        statebtn3 = true;
    }
}
