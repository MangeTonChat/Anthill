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

    /*!
     * \brief Map Constructor
     * \param p_Scene, Link the scene pointer to the map
     */
    Map(QGraphicsScene* p_Scene): Scene(p_Scene){}

    ~Map();

    /*!
     * \brief Generate The map environment on the Scene
     * \param p_BorderSize in pixel it's a square
     * \param p_ObstaclePercentage
     * \param p_PercentageOfWall , percentage to create a continous obstacle wall
     * \param p_MaxWallLength , max length of the wall
     * \param p_MinWallLength , min length of the wall
     * \param p_FoodPercentage
     */
    void Generate(const int p_BorderSize, const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength, const double p_FoodPercentage );

protected:

    /*!
     * \brief GenerateBorder
     */
    void GenerateBorder();

    /*!
     * \brief GenerateObstacle
     * \param p_ObstaclePercentage
     * \param p_PercentageOfWall
     * \param p_MaxWallLength
     * \param p_MinWallLength
     */
    void GenerateObstacle(const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength);

    /*!
     * \brief GenerateFood
     * \param p_FoodPercentage
     */
    void GenerateFood(const double p_FoodPercentage);

    int m_iBorderSize;          /*!< Convenience storage */

    QGraphicsScene* Scene;      /*!< Current healthpoint */

protected slots :

    /*!
     * \brief RegenerateFood each time a food object is destroyed
     */
    void RegenerateFood(QObject*);


};

#endif // MAP_H
