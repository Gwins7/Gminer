#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "windows.h"

#define TIME_ADDR 0x0100579C
#define TIME_RUN_ADDR 0x01005164
#define MINE_NUM_ADDR 0x010056A4
#define LENGTH_ADDR 0x010056A8
#define WIDTH_ADDR 0x010056AC
#define CONTROL_ADDR 0x01005000

#define MINE_MATRIX_START_ADDR 0x01005340
#define MINE_MATRIX_END_ADDR 0x0100567F

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    void BindSet(bool status);

    HWND hWnd;
    DWORD pid;
    HANDLE hProcess;

    DWORD length;
    DWORD width;
    DWORD mine_num;
    DWORD cur_time;

    short gameX = 20;
    short gameY = 62;
    double dpi = 1;
};
#endif // MAINWINDOW_H
