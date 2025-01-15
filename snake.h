#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>

class Snake {
public:
    Snake();
    void move();
    void grow();
    QList<QPoint> getBody() const;
    QPoint getHead() const;
    void setDirection(int dx, int dy);
    bool checkCollision() const; // Новый метод для проверки столкновения
    void reset(); // Новый метод для сброса состояния змейки

private:
    QList<QPoint> body;
    int directionX;
    int directionY;
};

#endif // SNAKE_H
