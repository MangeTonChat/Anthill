#include "queen.h"


static constexpr int PercentageOfLay = 80;
static constexpr int OddsOfLayingQueen = 10;
static constexpr int TimeToWaitBeforeLaying = 2500;
static constexpr int FoodConsumptionToLay = 1;
constexpr qreal Pi = M_PI;


Queen::Queen(Anthill* p_pAnthill, bool shouldILeave) : MovingAnt(p_pAnthill) , m_bShouldILeave(shouldILeave)
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.5; // queen is bigger

    colorAntType = QColor(Qt::blue);

    //To indicate this queen won't migrate
    m_bIsAQueen=false;

    timer.start();
}

void Queen::Attack(MovingAnt* Enemy)
{
    Enemy->takeDamage(QRandomGenerator::global()->bounded(20,25));
}


void Queen::advance(int step)
{
    if (!step)
        return;

    if(!m_bShouldILeave)
    {
        MovingAnt::advance(step);

        if(timer.elapsed()>TimeToWaitBeforeLaying){
            if(m_pAnthillOwner->canLayEgg()){
                LayEgg();
            }
            timer.restart();
        }
    }
    else
    {
        // Grab item in a circle around the ant
        QPainterPath circleDetection;
        circleDetection.addEllipse(mapToScene(QPointF(0, -38*ScaleFactor)), 100 , 100);
        const QList<QGraphicsItem *> aroundItems = scene()->items(circleDetection);

        double l_dClosestDistToObstacle = 999;
        double l_dSpeedFactor = 999;
        int l_iRightOrLeft = 1 ;

        // When the space is free , and 10 seconds
        if(aroundItems.size() == 1 && aroundItems.first() == this && timer.elapsed() > 10000)
        {
            m_bShouldILeave = false;

            // Generate random color
            QPointF l_QueenCenter = mapToScene(QPointF(0,0));
            QColor l_colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                           QRandomGenerator::global()->bounded(256),
                           QRandomGenerator::global()->bounded(256));

            // Create New Anthill
            Anthill *anthill= new Anthill(qreal(100),l_colorAnthill);
            anthill->setPos(l_QueenCenter.x(),l_QueenCenter.y());
            scene()->addItem(anthill);

            // Change owner
            m_pAnthillOwner = anthill;
            colorAnthill = l_colorAnthill;

            timer.restart();

        }
        else
        {
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
            else if (speed > -3 ) // Reset speed if needed
                speed = -3;
        }


        setPos(mapToParent(0, speed));

    }
}

void Queen::LayEgg()
{
    if(QRandomGenerator::global()->bounded(0,100)<=PercentageOfLay)
    {
        if(m_pAnthillOwner->consumeFoodStock((FoodConsumptionToLay/100)*m_pAnthillOwner->getMaxFoodStock()))
        {
            Ant *egg = new Egg(m_pAnthillOwner);
            if(QRandomGenerator::global()->bounded(1,100)<=OddsOfLayingQueen)
            {
                egg->setIsQueen(true);
            }
            egg->setPos(mapToScene(QPointF(0,0)));
            scene()->addItem(egg);
        }
    }
}
