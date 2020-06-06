#include "warrior.h"

#include <QRandomGenerator>

Warrior::Warrior()
 {
     // randomly set first rotation and color
     setRotation(QRandomGenerator::global()->bounded(360 * 16));

     ScaleFactor = 0.3;

     colorAntType = QColor(Qt::red);

     colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                    QRandomGenerator::global()->bounded(256),
                    QRandomGenerator::global()->bounded(256));
 }
