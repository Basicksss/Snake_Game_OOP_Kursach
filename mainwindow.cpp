#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamemainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    GameMainWindow *GMW = new GameMainWindow();
    GMW->show();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{


}

