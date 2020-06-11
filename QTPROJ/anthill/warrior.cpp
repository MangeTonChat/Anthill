#include "warrior.h"

#include <QRandomGenerator>
#include <QGraphicsView>
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

Warrior::Warrior(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
 {

     // randomly set first rotation and color
     setRotation(QRandomGenerator::global()->bounded(360 * 16));

     ScaleFactor = 0.3;

     colorAntType = QColor(Qt::red);

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

void Warrior::moveAngleTowards(const QPointF& PointInSceneCoordinate)
{
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(PointInSceneCoordinate));

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
        moveAngleTowards(QPointF(0.0,0.0));
    }
    // Magic Trick
    else if (sin(angle) < 0) {
        angle += 0.25;
    }
    else if (sin(angle) > 0) {
        angle -= 0.25;
    }

    // TODO : Move Randomly to search for beef

    // TODO : Understand the following shit
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;
    speed = - speed;

    qreal dx = sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
