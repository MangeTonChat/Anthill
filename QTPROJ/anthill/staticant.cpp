#include "staticant.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

StaticAnt::StaticAnt(Anthill* p_pAnthill) : Ant(p_pAnthill)
{

}


StaticAnt::~StaticAnt()
{

}

QRectF StaticAnt::boundingRect() const
{
    // TODO : improve
    qreal adjust = 3.5;
        return QRectF(-35*ScaleFactor - adjust, -55*ScaleFactor - adjust,
                      70*ScaleFactor + adjust, 110*ScaleFactor + adjust);
}

QPainterPath StaticAnt::shape() const
{
    QPainterPath path;
    path.addRect(-35*ScaleFactor, -55*ScaleFactor, 70*ScaleFactor, 100*ScaleFactor);
    return path;
}
