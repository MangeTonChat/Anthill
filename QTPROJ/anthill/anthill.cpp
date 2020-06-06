#include "anthill.h"

#include <QPainter>

Anthill::Anthill()
{

}

QRectF Anthill::boundingRect() const
{
    qreal adjust = 200; // TODO C LA MERDE
    return QRectF(m_rRay - adjust, m_rRay - adjust,
                  m_rRay + adjust, m_rRay + adjust);
}

QPainterPath Anthill::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(0,0),m_rRay,m_rRay);
    return path;
}

void Anthill::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    // Circle, TODO : augmenter la largeur
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(-m_rRay,-m_rRay,m_rRay,m_rRay);
}


void Anthill::advance(int )
{
    // it doesn't move
}
