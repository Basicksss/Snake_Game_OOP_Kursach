#include "fieldwidget.h"
#include <QPainter>
#include <QDebug>

FieldWidget::FieldWidget(QWidget *parent): QWidget(parent), food(17, 15), gameStarted(false), score(0), fruitCount(0)
{
    setFixedSize(635, 525);
    setFocusPolicy(Qt::StrongFocus);
    timer.setInterval(100);
    connect(&timer, &QTimer::timeout, this, &FieldWidget::updateGame);
}

void FieldWidget::keyPressEvent(QKeyEvent *event) {
    if (gameOver) { // Проверяем, завершена ли игра
            if (event->key() == Qt::Key_R) { // Клавиша R для перезапуска игры
                restartGame();
            }
            return; // Не обрабатываем другие клавиши
        }
    if (!gameStarted) {
        // Начинаем игру при нажатии стрелки
        if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
                event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
            gameStarted = true; // Игра началась
            timer.start(); // Запускаем таймер
        }
        return; // Не обрабатываем другие клавиши до начала игры
    }

    if(event->key()==Qt::Key_Escape)
    {
        pauseGame();
    }

    switch (event->key()) {
    case Qt::Key_Up:
        snake.setDirection(0, -1);
        break;
    case Qt::Key_Down:
        snake.setDirection(0, 1);
        break;
    case Qt::Key_Left:
        snake.setDirection(-1, 0);
        break;
    case Qt::Key_Right:
        snake.setDirection(1, 0);
        break;
    case Qt::Key_R: // Клавиша R для перезапуска игры
        restartGame();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void FieldWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание
    QPoint snakeHead = snake.getHead();

    int startX = 25; // Начальная позиция по X
    int startY = 0; // Начальная позиция по Y

    //Отрисовка поля
    for (int row = 0; row < 15; row++) {
        for (int col = 0; col < 17; col++) {
            if ((row + col) % 2 == 0) {
                painter.setBrush(QColor(169, 215, 81));
            } else {
                painter.setBrush(QColor(162, 208, 73));
            }
            painter.fillRect(startX + col * CELLSIZE, startY + row * CELLSIZE, CELLSIZE, CELLSIZE, painter.brush());
        }
    }
    //Отрисовка змейки
    for(const QPoint &segment : snake.getBody())
    {
        int x = startX + segment.x() * CELLSIZE + (CELLSIZE - SNAKESIZE) / 2;
        int y = startY + segment.y() * CELLSIZE + (CELLSIZE - SNAKESIZE) / 2;
        if(segment.x() == snakeHead.x() && segment.y() == snakeHead.y())
        {
            painter.setBrush(QColor(78, 124, 246));
            painter.drawRoundedRect(x, y, SNAKESIZE, SNAKESIZE, SNAKESIZE / 2, SNAKESIZE / 2);
            drawEyes(painter, x, y); // Рисуем глаза на голове
        }
        else
        {
            painter.setBrush(QColor(78, 124, 246));
            painter.drawRect(x,y,SNAKESIZE, SNAKESIZE);
        }


    }

    // Отрисовка еды
    QPoint foodPosition = food.getPosition();
    painter.setBrush(QColor(231, 69, 28));
    int x = startX + foodPosition.x() * CELLSIZE + (CELLSIZE - FOODSIZE) / 2; // Используем QPoint::x()
    int y = startY + foodPosition.y() * CELLSIZE + (CELLSIZE - FOODSIZE) / 2; // Используем QPoint::y()
    painter.drawEllipse(x, y, FOODSIZE, FOODSIZE); // Рисуем еду как круг

    qDebug() << "Head Position:" << snake.getHead();
    qDebug() << "Food Position:" << food.getPosition();
    qDebug() << "Snake Body:" << snake.getBody();

}

void FieldWidget::updateGame() {
    if(gameOver)
    {
        return;
    }

    snake.move();

    QPoint newFoodPosition;
    bool validPosition = false;
    qDebug() << "Head Position:" << snake.getHead();
    qDebug() << "Food Position:" << food.getPosition();
    qDebug() << "Snake Body:" << snake.getBody();
    // Проверка на съедание еды
    if (snake.getHead() == food.getPosition()) {
        snake.grow();
        score += 10; // Увеличиваем очки на 10
        fruitCount++; // Увеличиваем количество собранных фруктов
        while(!validPosition)
        {
            food.respawn(17, 15); // Перемещение еды
            // Проверка, не находится ли новая позиция в теле змейки
            validPosition = true; // Сначала предполагаем, что позиция валидна
            for (const auto& segment : snake.getBody()) {
                if (segment == newFoodPosition) {
                    validPosition = false; // Если совпадает с телом змейки, позиция не валидна
                    break;
                }
            }
        }
        food.respawn(17, 15); // Перемещение еды
        updateLabels(); // Обновление лейблов

    }
    // Проверка на столкновение
    if (snake.checkCollision()) {
        gameOver = true;
        GameOverWindow *gow = new GameOverWindow(score,fruitCount);
        gow->show();
        return;
    }

    update(); // Перерисовка виджета
}

void FieldWidget::restartGame() {
    snake.reset(); // Сброс змейки
    food.respawn(17, 15); // Перемещение еды
    gameStarted = false; // Сброс флага начала игры
    gameOver = false;
    score = 0; // Сброс очков
    fruitCount = 0; // Сброс количества фруктов
    updateLabels(); // Обновление лейблов
}
void FieldWidget::setLabels(QLabel *scoreLbl, QLabel *fruitCountLbl) {
    scoreLabel = scoreLbl;
    fruitCountLabel = fruitCountLbl;
}
void FieldWidget::updateLabels() {
    scoreLabel->setText(QString("Score: %1").arg(score));
    fruitCountLabel->setText(QString("Fruits Collected: %1").arg(fruitCount));
}

void FieldWidget::drawEyes(QPainter &painter, int x, int y) {
    // Параметры для рисования глаз
    int eyeSize = SNAKESIZE / 2.5; // Размер глаз
    int eyeOffsetX = SNAKESIZE / 4; // Смещение по X для глаз
    int eyeOffsetY = SNAKESIZE / 4; // Смещение по Y для глаз

    // Рисуем глаза (белки)
    painter.setBrush(Qt::white);
    painter.drawEllipse(x + eyeOffsetX, y + eyeOffsetY, eyeSize, eyeSize); // Левый глаз
    painter.drawEllipse(x + eyeOffsetX * 3, y + eyeOffsetY, eyeSize, eyeSize); // Правый глаз

    // Рисуем зрачки (черные)
    painter.setBrush(Qt::black);
    painter.drawEllipse(x + eyeOffsetX + eyeSize / 4, y + eyeOffsetY + eyeSize / 4, eyeSize / 2, eyeSize / 2); // Левый зрачок
    painter.drawEllipse(x + eyeOffsetX * 3 + eyeSize / 4, y + eyeOffsetY + eyeSize / 4, eyeSize / 2, eyeSize / 2); // Правый зрачок
}

void FieldWidget::pauseGame() {
    isPaused = true;
    timer.stop(); // Останавливаем таймер
    EscWindow *EscW = new EscWindow(score, fruitCount);
    EscW->show(); // Открываем меню
}
void FieldWidget::resumeGame() {
    isPaused = false;
    timer.start(100); // Останавливаем таймер
    EscWindow *EscW = new EscWindow(score, fruitCount);
    EscW->close(); // Открываем меню
}


