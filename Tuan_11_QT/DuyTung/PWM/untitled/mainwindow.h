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
    void on_close_clicked();
    void on_start_clicked();
    void on_tru_clicked();
    void on_cong_clicked();
    void start_buzzer();
};

#endif // MAINWINDOW_H
