#include "warrior.h"

#include <QRandomGenerator>

Warrior::Warrior(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
 {

     // randomly set first rotation and color
     setRotation(QRandomGenerator::global()->bounded(360 * 16));

     ScaleFactor = 0.3;

     colorAntType = QColor(Qt::red);

 }

void Warrior::advance(int step)
{
    if (!step)
        return;

    // TODO : Don't go outside the Scene

    // TODO : Move Randomly to search for beef

    // TODO : Understand the following shit
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;
    speed = - speed;

    qreal dx = sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
