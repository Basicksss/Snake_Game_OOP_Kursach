#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"
#include "fieldwidget.h"

GameMainWindow::GameMainWindow(QDockWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
    setFixedSize(650,650);

    scoreLabel = new QLabel("Score: 0", this);
    fruitCountLabel = new QLabel("Fruits Collected: 0", this);

    QFont newFont("Arial",18);

    scoreLabel->setGeometry(30, 10, 300, 30);
    scoreLabel->setFont(newFont);
    fruitCountLabel->setGeometry(175, 10, 300, 30);
    fruitCountLabel->setFont(newFont);
    FieldWidget *fieldWidget = new FieldWidget(this);
    fieldWidget->setLabels(scoreLabel,fruitCountLabel);
    setWidget(fieldWidget);
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}
