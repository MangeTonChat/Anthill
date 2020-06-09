#include "worker.h"

#include <QRandomGenerator>

Worker::Worker(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.3;

    colorAntType = QColor(Qt::green);

}
