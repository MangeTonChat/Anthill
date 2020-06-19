#ifndef MAP_H
#define MAP_H
#include <QtWidgets>

#include "obstacle.h"


class Map
{
public:
    Map(QGraphicsScene* p_Scene): Scene(p_Scene){}
    ~Map();
    void Generate();
protected:
    int ObstacleQuantity;
    int FoodQuantity;
    QGraphicsScene* Scene;
};

#endif // MAP_H
