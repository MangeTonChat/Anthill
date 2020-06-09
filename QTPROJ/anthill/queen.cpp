#include "queen.h"

#include <QRandomGenerator>

Queen::Queen(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.5; // queen is bigger

    colorAntType = QColor(Qt::blue);


}
