#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setFixedSize(300,200);
    statusBar()->showMessage("Minesweep Cheat by Gwins7");
    BindSet(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BindSet(bool status){
    ui->comboBox->setEnabled(status);
    ui->pushButton_1->setEnabled(status);
    ui->pushButton_2->setEnabled(status);
    ui->pushButton_3->setEnabled(status);
    ui->pushButton_4->setEnabled(status);
    ui->pushButton_5->setEnabled(status);
    ui->checkBox->setEnabled(status);
}

void MainWindow::on_pushButton_clicked() // binding process
{
    hWnd = FindWindow(NULL, L"Minesweeper");
    if (!hWnd) {
        statusBar()->showMessage("Game haven't start!");
        return;
    }

    GetWindowThreadProcessId(hWnd, &pid);
    hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        statusBar()->showMessage("Getting game process error!");
        return;
    }
    statusBar()->showMessage("Getting game process complete!");
    BindSet(true);
    ui->pushButton_1->click();
}


void MainWindow::on_pushButton_1_clicked() // refresh info
{
    ::ReadProcessMemory(hProcess, (LPCVOID)TIME_ADDR, &cur_time,
                        sizeof(cur_time), NULL);
    ::ReadProcessMemory(hProcess, (LPCVOID)MINE_NUM_ADDR, &mine_num,
                        sizeof(mine_num), NULL);
    ::ReadProcessMemory(hProcess, (LPCVOID)LENGTH_ADDR, &length,
                        sizeof(length), NULL);
    ::ReadProcessMemory(hProcess, (LPCVOID)WIDTH_ADDR, &width,
                        sizeof(width), NULL);
    ui->label_5->setText(QString::number(cur_time));
    ui->label_6->setText(QString::number(mine_num));
    ui->label_7->setText(QString::number(length));
    ui->label_8->setText(QString::number(width));
}


void MainWindow::on_pushButton_2_clicked() // clear time
{
    cur_time = 0;
    ::WriteProcessMemory(hProcess, (LPVOID)TIME_ADDR, &cur_time,
                        sizeof(cur_time), NULL);
}


void MainWindow::on_pushButton_3_clicked() // stop time
{
    DWORD i = 0;
    ::WriteProcessMemory(hProcess, (LPVOID)TIME_RUN_ADDR, &i,
                         sizeof(i), NULL);
}


void MainWindow::on_pushButton_4_clicked() // reborn
{
    DWORD i = 1;
    ::WriteProcessMemory(hProcess, (LPVOID)CONTROL_ADDR, &i,
                         sizeof(i), NULL);
}


void MainWindow::on_pushButton_5_clicked() // auto win
{
    DWORD l, w;
    unsigned char val;
    short pos[2];
    for (l=1;l<=length;l++){
        for (w=1;w<=width;w++){
            ::ReadProcessMemory(hProcess,
                                (LPCVOID)(unsigned long long)(MINE_MATRIX_START_ADDR + 0x20 * l + w),
                                &val,sizeof(val), NULL);
            pos[0] = (gameX + ((w-1) * 16)) * dpi;
            pos[1] = (gameY + ((l-1) * 16)) * dpi;
            if (val == 0x8F){
                if (ui->checkBox->isChecked()){
                    ::PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, *(int *)pos);
                    ::PostMessage(hWnd, WM_RBUTTONUP, 0, *(int *)pos);
                }

            }
            else if (val == 0x0F){
                if (!ui->checkBox->isChecked()){
                    ::PostMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, *(int *)pos);
                    ::PostMessage(hWnd, WM_LBUTTONUP, 0, *(int *)pos);
                }
            }
        }
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    switch (index) {
    case 0:
        dpi = 1;
        break;
    case 1:
        dpi = 1.25;
        break;
    case 2:
        dpi = 1.5;
        break;
    case 3:
        dpi = 2;
        break;
    }
}

