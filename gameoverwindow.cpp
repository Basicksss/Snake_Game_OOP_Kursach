#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

GameOverWindow::GameOverWindow(int score, int fruitCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
    scoreLabel = new QLabel("Score: " + QString::number(score), this);
    fruitCountLabel = new QLabel("Fruits Collected: " + QString::number(fruitCount), this);
    QFont newFont("Arial",18);

    scoreLabel->setGeometry(30, 10, 300, 30);
    scoreLabel->setFont(newFont);
    fruitCountLabel->setGeometry(175, 10, 300, 30);
    fruitCountLabel->setFont(newFont);

}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}

void GameOverWindow::on_pushButton_clicked()
{
    this->close();
}

