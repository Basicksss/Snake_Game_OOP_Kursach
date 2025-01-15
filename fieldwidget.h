#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include "food.h"
#include "snake.h"
#include "gameoverwindow.h"
#include "escwindow.h"

class FieldWidget : public QWidget
{
public:
    FieldWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void drawEyes(QPainter &painter, int x, int y);

public slots:
    void updateGame();
    void restartGame(); // Новый слот для перезапуска игры
    void setLabels(QLabel *scoreLbl, QLabel *fruitCountLbl);

private:
    Snake snake;
    Food food;
    QTimer timer;
    bool gameStarted; // Флаг, указывающий, началась ли игра
    bool isPaused;
    void pauseGame();
    void resumeGame();

    // Новые переменные для очков и количества фруктов
    int score;
    int fruitCount;
    bool gameOver = false;

    const int CELLSIZE = 35; // Размер клетки
    const int FOODSIZE = CELLSIZE / 2;
    const int SNAKESIZE = 35;

    // Лейблы для отображения очков и количества фруктов
    QLabel *scoreLabel;
    QLabel *fruitCountLabel;

    void updateLabels(); // Новый метод для обновления лейблов
};

#endif // FIELDWIDGET_H
