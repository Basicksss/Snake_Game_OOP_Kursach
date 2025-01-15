#ifndef FOOD_H
#define FOOD_H

#include <QPoint>

class Food {
public:
    Food(int width, int height);
    QPoint getPosition() const;
    void respawn(int width, int height);

private:
    QPoint position;
};

#endif // FOOD_H
