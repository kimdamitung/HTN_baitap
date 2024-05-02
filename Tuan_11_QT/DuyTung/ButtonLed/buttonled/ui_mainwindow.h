/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 2 18:28:57 2024
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *led0;
    QFrame *led1;
    QFrame *led3;
    QFrame *led2;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        led0 = new QFrame(centralWidget);
        led0->setObjectName(QString::fromUtf8("led0"));
        led0->setGeometry(QRect(130, 10, 50, 50));
        led0->setStyleSheet(QString::fromUtf8(""));
        led0->setFrameShape(QFrame::StyledPanel);
        led0->setFrameShadow(QFrame::Raised);
        led1 = new QFrame(centralWidget);
        led1->setObjectName(QString::fromUtf8("led1"));
        led1->setGeometry(QRect(130, 60, 50, 50));
        led1->setStyleSheet(QString::fromUtf8(""));
        led1->setFrameShape(QFrame::StyledPanel);
        led1->setFrameShadow(QFrame::Raised);
        led3 = new QFrame(centralWidget);
        led3->setObjectName(QString::fromUtf8("led3"));
        led3->setGeometry(QRect(130, 160, 50, 50));
        led3->setStyleSheet(QString::fromUtf8(""));
        led3->setFrameShape(QFrame::StyledPanel);
        led3->setFrameShadow(QFrame::Raised);
        led2 = new QFrame(centralWidget);
        led2->setObjectName(QString::fromUtf8("led2"));
        led2->setGeometry(QRect(130, 110, 50, 50));
        led2->setStyleSheet(QString::fromUtf8(""));
        led2->setFrameShape(QFrame::StyledPanel);
        led2->setFrameShadow(QFrame::Raised);
        btn0 = new QPushButton(centralWidget);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setGeometry(QRect(200, 20, 89, 27));
        btn0->setStyleSheet(QString::fromUtf8(""));
        btn1 = new QPushButton(centralWidget);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(200, 70, 89, 27));
        btn1->setStyleSheet(QString::fromUtf8(""));
        btn2 = new QPushButton(centralWidget);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(200, 120, 89, 27));
        btn2->setStyleSheet(QString::fromUtf8(""));
        btn3 = new QPushButton(centralWidget);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(200, 170, 89, 27));
        btn3->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btn0->setText(QApplication::translate("MainWindow", "LED 0", 0, QApplication::UnicodeUTF8));
        btn1->setText(QApplication::translate("MainWindow", "LED 1", 0, QApplication::UnicodeUTF8));
        btn2->setText(QApplication::translate("MainWindow", "LED 2", 0, QApplication::UnicodeUTF8));
        btn3->setText(QApplication::translate("MainWindow", "LED 3", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
