#include "movingant.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

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

MovingAnt::MovingAnt(Anthill* p_pAnthill) : Ant(p_pAnthill)
{

}

MovingAnt::~MovingAnt()
{

}

QRectF MovingAnt::boundingRect() const
{
    // TODO : improve
    qreal adjust = 3.5;
        return QRectF(-35*ScaleFactor - adjust, -55*ScaleFactor - adjust,
                      70*ScaleFactor + adjust, 110*ScaleFactor + adjust);
}

QPainterPath MovingAnt::shape() const
{
    QPainterPath path;
    path.addRect(-35*ScaleFactor, -55*ScaleFactor, 70*ScaleFactor, 100*ScaleFactor);
    return path;
}

void MovingAnt::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Pates arrière droite
    QPainterPath pathAD(QPointF(-5*ScaleFactor, 13*ScaleFactor));
    pathAD.cubicTo(-5*ScaleFactor, 13*ScaleFactor, -30*ScaleFactor, 25*ScaleFactor, -35*ScaleFactor, +55*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAD);

    // Pates arrière gauche
    QPainterPath pathAG(QPointF(5*ScaleFactor, 13*ScaleFactor));
    pathAG.cubicTo(5*ScaleFactor, 13*ScaleFactor, 30*ScaleFactor, 25*ScaleFactor, 35*ScaleFactor, 55*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAG);

    // Pates mid droite
    QPainterPath pathMD(QPointF(-8*ScaleFactor, 5*ScaleFactor));
    pathMD.cubicTo(-8*ScaleFactor, 5*ScaleFactor, -20*ScaleFactor, 2*ScaleFactor, -35*ScaleFactor, -10*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathMD);

    // Pates mid gauche
    QPainterPath pathMG(QPointF(8*ScaleFactor, 5*ScaleFactor));
    pathMG.cubicTo(8*ScaleFactor, 5*ScaleFactor, 20*ScaleFactor, 2*ScaleFactor, 35*ScaleFactor, -10*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathMG);

    // Pates avant droite
    QPainterPath pathAvD(QPointF(-8*ScaleFactor, -10*ScaleFactor));
    pathAvD.cubicTo(-8*ScaleFactor, -10*ScaleFactor, -20*ScaleFactor, -7*ScaleFactor, -35*ScaleFactor, -30*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAvD);

    // Pates avant gauche
    QPainterPath pathAvG(QPointF(-8*ScaleFactor, -10*ScaleFactor));
    pathAvG.cubicTo(8*ScaleFactor, -10*ScaleFactor, 20*ScaleFactor, -7*ScaleFactor, 35*ScaleFactor, -30*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAvG);

    // Body below
    painter->setBrush(colorAnthill);
    painter->drawEllipse(-15*ScaleFactor, 15*ScaleFactor, 30*ScaleFactor, 40*ScaleFactor);

    // Body Middle
    //painter->setBrush(scene()->collidingItems(this).isEmpty() ? colorAntType : Qt::green);
    painter->setBrush(colorAntType);
    painter->drawEllipse(-10*ScaleFactor, -15*ScaleFactor, 20*ScaleFactor, 30*ScaleFactor);

    // Head
    painter->setBrush(colorAntType);
    painter->drawEllipse(-10*ScaleFactor, -35*ScaleFactor, 20*ScaleFactor, 20*ScaleFactor);

    // Eyes
    painter->setBrush(Qt::black);
    painter->drawEllipse(-9*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);
    painter->drawEllipse(1*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);

    // Healthbar
    if(m_iHealthPoints < MaxHealthPoint)
    {
        painter->setBrush(Qt::green);
        painter->drawRect(-15,-20,30,5);
        painter->setBrush(Qt::red);
        painter->drawRect(-15,-20,30*(1- ((double)m_iHealthPoints/MaxHealthPoint)),5);
    }

}


void MovingAnt::advance(int step)
{
    if (!step)
        return;

    // Hungry Ant
    if(!eatToSurvive())
        return;

    // Line beetween ant and anthill center
    QLineF lineToCenter(QPointF(0, 0), mapFromItem(m_pAnthillOwner,QPointF(0.0,0.0)));

    // Not move away from the anthill, -20 because the calcul is based on ant center
    if (lineToCenter.length() > m_pAnthillOwner->getRay() - 20)
    {
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
    else if (::sin(angle) < 0) {
        angle += 0.25;
    }
    else if (::sin(angle) > 0) {
        angle -= 0.25;
    }

   // const QList<QGraphicsItem *> aroundItems= scene()->collidingItems(this);
    QPainterPath circleDetection;
    circleDetection.addEllipse(mapToScene(QPointF(0, -38*ScaleFactor)), 46 , 46);
    const QList<QGraphicsItem *> aroundItems = scene()->items(circleDetection);

    bool isThereEnemies = false; // To reset Speed
    bool l_bCanAttack = true;

    // Search for others items
    for (QGraphicsItem *item : aroundItems)
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
                    //moveAngleTowards(mapFromItem(Enemy, QPointF(0,0))); // Incline towards the enemy
                    //QLineF lineToCenter(QPointF(0, 0), mapFromItem(Enemy, QPointF(0,0))); // Idea to decrease speed as enemy come closer
                    speed -= speed*0.09; // Reduce speed from 9% each frame
                    Attack(Enemy); // ATTACK DA ENEMY , 1 - 10 damage
                    isThereEnemies= true; // sweatflag
                }
                l_bCanAttack = false;
                continue;
            }
        }
    }

    if (speed > -3 && !isThereEnemies) // Reset speed if needed
            speed = -3;



    qreal dx = sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, speed));
}
