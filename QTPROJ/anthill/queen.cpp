#include "queen.h"

#include <QRandomGenerator>

Queen::Queen()
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.5; // queen is bigger

    colorAntType = QColor(Qt::blue);

    colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256));

}
