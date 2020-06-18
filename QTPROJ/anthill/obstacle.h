#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>

class Obstacle : public QGraphicsPixmapItem
{
    public:
    Obstacle(QPixmap pixmap) : QGraphicsPixmapItem(pixmap){}
    virtual ~Obstacle(){}
};

#endif // OBSTACLE_H
