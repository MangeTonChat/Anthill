#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QObject>
#include <QtMath>
#include <QDebug>

#include "obstacle.h"
#include "Beef.h"


class Map : public QObject
{
    Q_OBJECT

public:
    Map(QGraphicsScene* p_Scene): Scene(p_Scene){}

    ~Map();

    void Generate(const int p_BorderSize, const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength, const double p_FoodPercentage );

protected:

    void GenerateBorder();

    void GenerateObstacle(const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength);

    void GenerateFood(const double p_FoodPercentage);

    int m_iBorderSize;

    QGraphicsScene* Scene;

protected slots :

    void RegenerateFood(QObject*);


};

#endif // MAP_H
