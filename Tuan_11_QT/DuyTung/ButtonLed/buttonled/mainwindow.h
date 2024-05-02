#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_btn3_clicked();
    void on_btn2_clicked();
    void on_btn1_clicked();
    void on_btn0_clicked();
    void xuly_button();
};

#endif // MAINWINDOW_H
