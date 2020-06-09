#include "anthill.h"

#include <QPainter>

Anthill::Anthill() : m_rRay(200)
{

}

QRectF Anthill::boundingRect() const
{
    qreal adjust = 3; // Below-left , not top-left
    return QRectF( - m_rRay - adjust,  - m_rRay - adjust,
                  2*m_rRay + adjust, 2*m_rRay + adjust);
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

    painter->drawEllipse(-m_rRay,-m_rRay,2*m_rRay,2*m_rRay);
    painter->setBrush(Qt::green);
}


void Anthill::advance(int )
{
    // it doesn't move
}
