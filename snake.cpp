#include "snake.h"

Snake::Snake() {
    reset(); // Инициализация при создании
}

void Snake::move() {
    QPoint newHead = getHead() + QPoint(directionX, directionY);
    body.prepend(newHead); // Добавляем новую голову в начало
    body.removeLast(); // Убираем последний элемент (хвост)
}

void Snake::grow() {
    // Добавляем новый сегмент в позицию последнего сегмента тела
        QPoint lastSegment = body.last(); // Получаем координаты последнего сегмента
        QPoint newSegment = lastSegment; // Создаем новый сегмент на основе последнего

        // В зависимости от направления, устанавливаем координаты нового сегмента
        newSegment.setX(newSegment.x() - directionX); // Если направление X, уменьшаем X
        newSegment.setY(newSegment.y() - directionY); // Если направление Y, уменьшаем Y

        body.append(newSegment); // Добавляем новый сегмент в конец списка
}

QList<QPoint> Snake::getBody() const {
    return body;
}

QPoint Snake::getHead() const {
    return body.first();
}

void Snake::setDirection(int dx, int dy) {
    if ((dx == -directionX && dy == -directionY) || (dx == 0 && dy == 0)) {
            return; // Игнорируем попытку изменить направление на противоположное
    }
    directionX = dx;
    directionY = dy;
}

bool Snake::checkCollision() const {
    // Проверка столкновения с самой собой
    for (int i = 1; i < body.size(); ++i) {
        if (body[i] == getHead()) {
            return true;
        }
    }
    // Проверка столкновения с границами
    // Получаем координаты головы змейки
        QPoint head = getHead();

        // Проверка столкновения с границами поля
        const int fieldWidth = 17; // Ширина поля в пикселях
        const int fieldHeight = 15; // Высота поля в пикселях

        if (head.x() < 0 || head.x() >= fieldWidth || head.y() < 0 || head.y() >= fieldHeight) {
            return true; // Столкновение с границей поля
        }

    return false;
}

void Snake::reset() {
    body.clear();
    body.append(QPoint(5, 5)); // Начальная позиция головы змейки
    directionX = 1; // Начальное направление движения (вправо)
    directionY = 0;
}
