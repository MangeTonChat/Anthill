#include "warrior.h"

#include <QRandomGenerator>
#include <QGraphicsView>
#include <QtMath>
#include <QDebug>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Warrior::Warrior(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
 {

     // randomly set first rotation and color
     setRotation(QRandomGenerator::global()->bounded(360 * 16));

     ScaleFactor = 0.3;

     colorAntType = QColor(Qt::red);

 }

void Warrior::Attack(Warrior* Enemy, int damage)
{
    Enemy->m_iHealthPoints-=damage;

    if(Enemy->m_iHealthPoints <0)
    {
        Enemy->Die();
    }

}

bool Warrior::isCloseToBorder() const
{
    int l_iBorderSize = 90;

    if(qFabs(mapToScene(QPointF(0,0)).x()) > (scene()->width()/2) - l_iBorderSize)
        return true;

    if(qFabs(mapToScene(QPointF(0,0)).y()) > (scene()->height()/2) - l_iBorderSize)
        return true;

    return false;
}

void Warrior::moveAngleTowards(const QPointF& PointInItemCoordinate)
{
    QLineF lineToCenter(QPointF(0, 0), PointInItemCoordinate);

    qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
    angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

    if (angleToCenter < Pi && angleToCenter > Pi / 4)
    {
        // Rotate left
        angle += (angle < -Pi / 2) ? 0.25 : -0.25;
    }
    else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4))
    {
        // Rotate right
        angle += (angle < Pi / 2) ? 0.25 : -0.25;
    }
}



void Warrior::advance(int step)
{
    if (!step)
        return;

    // Don't go outside the Scene Border
    if(isCloseToBorder())
    {
        moveAngleTowards(mapFromScene(QPointF(0.0,0.0))); // Move towards the scene center

    }
    // Magic Trick
    else if (sin(angle) < 0) {
        angle += 0.25;
    }
    else if (sin(angle) > 0) {
        angle -= 0.25;
    }

    // Final compute for angle and position
    qreal dx = sin(angle) * 10;
    setRotation(rotation() + dx);

    // Grab item in a circle around the ant
    QPainterPath circleDetection;
    circleDetection.addEllipse(mapToScene(QPointF(0, -38*ScaleFactor)), 46 , 46);
    const QList<QGraphicsItem *> aroundItems = scene()->items(circleDetection);
    /*const QList<QGraphicsItem *> aroundItems= scene()->collidingItems(this);*/

    //qDebug() << "nombre en contact : " << aroundItems.size();

    bool isThereEnemies = false; // To reset Speed
    double l_dClosestDistToObstacle = 999;
    double l_dSpeedFactor = 999;
    int l_iRightOrLeft = 1 ; // 1 right , -1 left

    // Search for others items
    for (QGraphicsItem *item : aroundItems)
    {
        if (item == this) // No action for self
            continue;

        // Obstacle Check
        Obstacle* obstacle = dynamic_cast<Obstacle*>(item);

        // if cast is sucessfull
        if (obstacle)
        {
            // Line, head to
            QPointF obstacleCenter = mapFromItem(obstacle,QPointF(64,64));
            QLineF lineToObstacle(QPointF(0, -38*ScaleFactor), obstacleCenter);

            // Reduce speed in order to not collide with the obstacle
            double obstacleRay = (64/2)*std::sqrt(2); // Width is 64 , 32 , circle around the obstacle
            double distToStop = 30; // pixel to slow down to speed = 0
            double distToBeginSlowDown = obstacleRay + distToStop;

            double speedFactor = -((lineToObstacle.length() - distToBeginSlowDown ) / distToStop);

            if(lineToObstacle.length() <= distToBeginSlowDown && lineToObstacle.length() <  l_dClosestDistToObstacle)
            {
                // Store needed data
                l_dClosestDistToObstacle = lineToObstacle.length(); // just take the closest one into account
                l_dSpeedFactor = speedFactor;

                // Check the quad
                qreal Quad = std::atan2((obstacleCenter.y() > 0 ) ? 1 : -1, (obstacleCenter.x() > 0) ? 1 : -1);

                /*if (Quad <= Pi / 2  && Quad >= -Pi /2 )
                {
                    // Rotate right
                    l_iRightOrLeft = 1;
                }
                else
                {
                    // Rotate left
                    l_iRightOrLeft = -1;
                }*/

                if  ( Quad > - Pi && Quad < -Pi/2) // Quad 3
                {
                    // Rotate right
                    l_iRightOrLeft = 1;
                    qDebug() << " Quad 3 ";
                }
                else if ( Quad < 0    && Quad > - Pi / 2 )// Quad 4
                {
                    // Rotate left
                    l_iRightOrLeft = -1;
                    qDebug() << " Quad 4 ";
                }
                else if ( Quad > 0    && Quad < Pi /2) // Quad 1
                {
                    l_dClosestDistToObstacle = 999;
                    qDebug() << " Quad 1 ";
                }
                else
                {
                    l_dClosestDistToObstacle = 999;
                    qDebug() << " Quad 2 ";
                }


                /*
                 * if ( Quad > 0    && Quad < Pi /2) // Quad 1
                 * if ( Quad > Pi/2 && Quad < Pi ) // Quad 2
                 * if ( Quad < 0    && Quad > - Pi / 2 )// Quad 4
                 * if ( Quad > - Pi && Quad < -Pi/2) // Quad 3
                */

            }

        }

        // Warrior Check
        Warrior* Enemy = dynamic_cast<Warrior*>(item);

        // If cast is sucessfull
        if(Enemy)
        {
            // If its not an ant from Home Anthill
            if (Enemy->getAnthill() != m_pAnthillOwner)
            {
                // FIGHT
                moveAngleTowards(mapFromItem(Enemy, QPointF(0,0))); // Incline towards the enemy
                //QLineF lineToCenter(QPointF(0, 0), mapFromItem(Enemy, QPointF(0,0))); // Idea to decrease speed as enemy come closer
                speed -= speed*0.05; // Reduce speed from 4% each frame
                Attack(Enemy,QRandomGenerator::global()->bounded(10)); // ATTACK DA ENEMY , 1 - 10 damage
                isThereEnemies= true; // sweatflag
            }
            //continue;
        }
    }

    // Final obstacle managment
    if(l_dClosestDistToObstacle != 999)
    {
            // Compute new speed
            l_dSpeedFactor = (l_dSpeedFactor <= 1) ? l_dSpeedFactor : 1 ;

            speed =  -3*( 1 - l_dSpeedFactor);

            if (speed > -0.09 ) speed = 0 ; // Round problem

            // rotation
            setRotation(rotation() + 5*l_iRightOrLeft);

            // Other magic trick
            if(speed ==0 )
                setRotation(rotation() + 30);

    }
    else if (speed > -3 && !isThereEnemies)
        speed = -3;


   /*// Reset Speed if needed
    if (speed > -3  && !isThereEnemies )
        speed = -3;*/

    // TODO : Move Randomly to search for beef

    // Final compute for angle and position
    //qreal dx = sin(angle) * 10;
    //qDebug() << " dx : " << dx << " / angle : " << angle << " / rotation() + dx " << rotation() + dx;

    //setRotation(rotation() + dx);
    setPos(mapToParent(0, speed));
}
