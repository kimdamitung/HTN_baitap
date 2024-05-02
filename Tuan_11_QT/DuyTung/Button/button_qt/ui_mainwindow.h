/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Apr 25 18:38:00 2024
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
    QPushButton *btnK1;
    QPushButton *btnK2;
    QPushButton *btnK3;
    QPushButton *btnK4;
    QPushButton *btnK5;
    QPushButton *btnK6;
    QPushButton *btnK7;
    QPushButton *btnK8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btnK1 = new QPushButton(centralWidget);
        btnK1->setObjectName(QString::fromUtf8("btnK1"));
        btnK1->setGeometry(QRect(10, 10, 98, 27));
        btnK2 = new QPushButton(centralWidget);
        btnK2->setObjectName(QString::fromUtf8("btnK2"));
        btnK2->setGeometry(QRect(10, 50, 98, 27));
        btnK3 = new QPushButton(centralWidget);
        btnK3->setObjectName(QString::fromUtf8("btnK3"));
        btnK3->setGeometry(QRect(10, 80, 98, 27));
        btnK4 = new QPushButton(centralWidget);
        btnK4->setObjectName(QString::fromUtf8("btnK4"));
        btnK4->setGeometry(QRect(10, 120, 98, 27));
        btnK5 = new QPushButton(centralWidget);
        btnK5->setObjectName(QString::fromUtf8("btnK5"));
        btnK5->setGeometry(QRect(130, 10, 98, 27));
        btnK6 = new QPushButton(centralWidget);
        btnK6->setObjectName(QString::fromUtf8("btnK6"));
        btnK6->setGeometry(QRect(130, 60, 98, 27));
        btnK7 = new QPushButton(centralWidget);
        btnK7->setObjectName(QString::fromUtf8("btnK7"));
        btnK7->setGeometry(QRect(130, 90, 98, 27));
        btnK8 = new QPushButton(centralWidget);
        btnK8->setObjectName(QString::fromUtf8("btnK8"));
        btnK8->setGeometry(QRect(140, 130, 98, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btnK1->setText(QApplication::translate("MainWindow", "Key1", 0, QApplication::UnicodeUTF8));
        btnK2->setText(QApplication::translate("MainWindow", "Key2", 0, QApplication::UnicodeUTF8));
        btnK3->setText(QApplication::translate("MainWindow", "Key3", 0, QApplication::UnicodeUTF8));
        btnK4->setText(QApplication::translate("MainWindow", "Key4", 0, QApplication::UnicodeUTF8));
        btnK5->setText(QApplication::translate("MainWindow", "Key5", 0, QApplication::UnicodeUTF8));
        btnK6->setText(QApplication::translate("MainWindow", "Key6", 0, QApplication::UnicodeUTF8));
        btnK7->setText(QApplication::translate("MainWindow", "Key7", 0, QApplication::UnicodeUTF8));
        btnK8->setText(QApplication::translate("MainWindow", "Key8", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
