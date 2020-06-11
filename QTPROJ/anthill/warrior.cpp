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
        speed = -3;
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

    // Grab items in a triangle in front of the ant
    /*const QList<QGraphicsItem *> aroundItems = scene()->items(QPolygonF()
                           << mapToScene(0, 0)
                           << mapToScene(-40, -60)
                           << mapToScene(40, -60));*/

    // Grab item in a circle around the ant
    QPainterPath circleDetection;
    circleDetection.addEllipse(mapToScene(QPointF(0,0)), 60 , 60);
    const QList<QGraphicsItem *> aroundItems = scene()->items(circleDetection);

    bool isThereEnemies = false; // To reset Speed

    // Search for enemy
    for (QGraphicsItem *item : aroundItems)
    {
        if (item == this) // No action for self
            continue;

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
                speed -= speed*0.04; // Reduce speed from 4% each frame
                Attack(Enemy,QRandomGenerator::global()->bounded(10)); // ATTACK DA ENEMY , 1 - 10 damage
                isThereEnemies= true; // sweatflag
            }

        }

    }

    // Reset Speed if needed
    if (speed > -3  && !isThereEnemies )
        speed = -3;

    // TODO : Move Randomly to search for beef

    // Final compute for angle and position
    qreal dx = sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, speed));
}
