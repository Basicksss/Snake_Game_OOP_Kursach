#include "food.h"
#include <QRandomGenerator>

Food::Food(int width, int height) {
    respawn(width, height);
}

QPoint Food::getPosition() const {
    return position;
}

void Food::respawn(int width, int height) {
    int x = rand() % (width); // Предполагается, что размер клетки 10x10
        int y = rand() % (height);
        position = QPoint(x, y);
}
