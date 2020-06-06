#include "worker.h"

#include <QRandomGenerator>

Worker::Worker()
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.3;

    colorAntType = QColor(Qt::green);

    colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256));

}
