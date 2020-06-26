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

Warrior::Warrior(Anthill* p_pAnthill) : MovingAnt(p_pAnthill), m_bOnMyWayHome(false),m_bOnMyWayAway(false), FoodStock(0)
{
     // randomly set first rotation and color
     setRotation(QRandomGenerator::global()->bounded(360 * 16));

     ScaleFactor = 0.3;

     colorAntType = QColor(Qt::red);

 }

void Warrior::Attack(MovingAnt* Enemy)
{
    Enemy->takeDamage(QRandomGenerator::global()->bounded(5,10));
}

void Warrior::paint(QPainter *painter, const QStyleOptionGraphicsItem *_1, QWidget *_2)
{
    MovingAnt::paint(painter,_1,_2);

    // TODO : Possible animation quand la fourmis attaque
    /*
    bool isAttacking = true;

    if(isAttacking)
    {

    }*/
}


void Warrior::moveAngleTowards(const QPointF& PointInItemCoordinate)
{
    QLineF lineToCenter(QPointF(0, 0), PointInItemCoordinate);

    // Compute angle to the other point
    qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
    angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

    int l_iAngleStep = 10; // Magic value

    // Rotate towards the point
    if (angleToCenter < Pi && angleToCenter > Pi / 4)
    {
        // Rotate left
        setRotation(rotation() + ((angle < -Pi / 2) ? l_iAngleStep : -l_iAngleStep));
    }
    else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4))
    {
        // Rotate right
        setRotation(rotation() + ((angle < Pi / 2) ? l_iAngleStep : -l_iAngleStep));
    }
}



void Warrior::advance(int step)
{
    if (!step)
        return;

    // Grab item in a circle around the ant
    QPainterPath circleDetection;
    circleDetection.addEllipse(mapToScene(QPointF(0, -38*ScaleFactor)), 46 , 46);
    const QList<QGraphicsItem *> aroundItems = scene()->items(circleDetection);
    /*const QList<QGraphicsItem *> aroundItems= scene()->collidingItems(this);*/

    bool isThereEnemies = false; // To reset Speed
    bool isThereBeef = false;
    bool l_bCanAttack = true;

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
            // Line, head to obstacle center
            QPointF obstacleCenter = mapFromItem(obstacle,QPointF(64,64));
            QLineF lineToObstacle(QPointF(0, -38*ScaleFactor), obstacleCenter);

            // Reduce speed in order to not collide with the obstacle
            double obstacleRay = (64/2)*std::sqrt(2); // Width is 64 , 32 , circle around the obstacle
            double distToStop = 20; // pixel to slow down to speed = 0
            double distToBeginSlowDown = obstacleRay + distToStop;

            // Compute the speed factor, to reduce speed if approching an obstacle
            double speedFactor = -((lineToObstacle.length() - distToBeginSlowDown ) / distToStop);

            // Check for the closest obstacle
            if(lineToObstacle.length() <= distToBeginSlowDown && lineToObstacle.length() <  l_dClosestDistToObstacle)
            {
                // Store needed data
                l_dClosestDistToObstacle = lineToObstacle.length(); // just take the closest one into account
                l_dSpeedFactor = speedFactor;

                // Check the quad
                qreal Quad = std::atan2((obstacleCenter.y() > 0 ) ? 1 : -1, (obstacleCenter.x() > 0) ? 1 : -1);

                if  ( Quad > - Pi && Quad < -Pi/2) // Quad 3
                {
                    // Rotate right
                    l_iRightOrLeft = 1;
                }
                else if ( Quad < 0    && Quad > - Pi / 2 )// Quad 4
                {
                    // Rotate left
                    l_iRightOrLeft = -1;
                }
                else // Quad 1 or 2
                {
                    // Don't Rotate
                    l_dClosestDistToObstacle = 999;
                }

                /*
                 * if ( Quad > 0    && Quad < Pi /2) // Quad 1
                 * if ( Quad > Pi/2 && Quad < Pi ) // Quad 2
                 * if ( Quad < 0    && Quad > - Pi / 2 )// Quad 4
                 * if ( Quad > - Pi && Quad < -Pi/2) // Quad 3
                */
            }    
            continue;
        }

        // Ignore beef and enemy while head back to the anthill
        if(!m_bOnMyWayHome)
        {
            // To attack only one ant per frame
            if ( l_bCanAttack )
            {
                // Warrior Check
                MovingAnt* Enemy = dynamic_cast<MovingAnt*>(item);

                // If cast is sucessfull
                if(Enemy)
                {
                    // If its not an ant from Home Anthill
                    if (Enemy->getAnthill() != m_pAnthillOwner)
                    {
                        // FIGHT
                        moveAngleTowards(mapFromItem(Enemy, QPointF(0,0))); // Incline towards the enemy
                        //QLineF lineToCenter(QPointF(0, 0), mapFromItem(Enemy, QPointF(0,0))); // Idea to decrease speed as enemy come closer
                        speed -= speed*0.09; // Reduce speed from 9% each frame
                        Attack(Enemy); // ATTACK DA ENEMY , 1 - 10 damage
                        isThereEnemies= true; // sweatflag
                    }
                    l_bCanAttack = false;
                    continue;
                }
            }

            // Beef Check
            Beef* SweatBeef = dynamic_cast<Beef*>(item);

            if(SweatBeef && FoodStock <= FoodCapacity)
            {
                int l_iUnitToEat = 10;
                if(SweatBeef->getEated(l_iUnitToEat))
                {
                    moveAngleTowards(mapFromItem(SweatBeef, QPointF(0,0))); // Incline towards the Beef
                    speed -= speed*0.15; // Reduce speed from 9% each frame
                    FoodStock+=l_iUnitToEat;
                    isThereBeef = true;

                    if(FoodStock > FoodCapacity)
                    {
                        m_bOnMyWayHome = true;
                        m_Timer.start();
                    }
                }
            }
        }
        else if(item == m_pAnthillOwner)
        {
            // FILL ANTHILL STOCK
            m_pAnthillOwner->bringMeFood(FoodStock);
            FoodStock = 0 ;
            m_bOnMyWayHome = false;
            m_bOnMyWayAway = false; // to be sure
        }

    }

    // Final obstacle managment
    if(l_dClosestDistToObstacle != 999)
    {
            // Round the speedFactor
            l_dSpeedFactor = (l_dSpeedFactor <= 1) ? l_dSpeedFactor : 1 ;

            // Compute new speed
            speed =  -3*( 1 - l_dSpeedFactor);

            if (speed > -0.09 ) speed = 0 ; // Round problem

            // set rotation
            setRotation(rotation() + 5*l_iRightOrLeft);

            // Other magic trick to escape from crazy angles
            if(speed ==0 )
                setRotation(rotation() + QRandomGenerator::global()->bounded(10,30));

    }
    else if (speed > -3 && !isThereEnemies && !isThereBeef ) // Reset speed if needed
        speed = -3;

    // GO HOME DUDE
    if(m_bOnMyWayHome && l_dClosestDistToObstacle == 999)
    {
        // If not trying to escape
        if(!m_bOnMyWayAway)
        {
            // Checck if it takes too much time
            if(m_Timer.elapsed() > 30000)
            {
                m_bOnMyWayAway = true;
                m_Timer.restart();
            }

            QPointF AnthillCenter = mapFromItem(m_pAnthillOwner, QPointF(0,0));

            int l_iAngleStep = 10; // Magic value

            qreal Quad = std::atan2((AnthillCenter.y() > 0 ) ? 1 : -1, (AnthillCenter.x() > 0) ? 1 : -1);
            qreal angleToAnthill = std::atan2(AnthillCenter.y(), AnthillCenter.x());

            if(angleToAnthill > (-5*Pi/9) && angleToAnthill < (-4*Pi/9)) // 80 / 100 deg
            {
                // don't change angle, it's in the right direction
            }
            else if  ( (Quad > - Pi && Quad < -Pi/2) || (Quad > Pi/2 && Quad < Pi)) // Quad 3 or 2
            {
                // Rotate right
                setRotation(rotation() - l_iAngleStep);
            }
            else //if ( (Quad < 0    && Quad > - Pi / 2) || ( Quad > 0  && Quad < Pi /2) ) // Quad 4 or 1
            {
                // Rotate left
                setRotation(rotation() + l_iAngleStep);
            }
        }
        // Move away for 10s, then retry
        else
        {
            if(m_Timer.elapsed() > 10000)
            {
                m_bOnMyWayAway = false;
                m_Timer.restart();
            }
        }
    }

    setPos(mapToParent(0, speed)); // Make it move !
}
