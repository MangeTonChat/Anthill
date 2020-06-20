#include "anthill.h"

#include <QPainter>
#include <QtDebug>

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

    // Foodbar
    painter->setBrush(Qt::green);
    painter->drawRect(-m_rRay, -m_rRay - 15,2*m_rRay,7);
    painter->setBrush(Qt::red);
    painter->drawRect(-m_rRay ,-m_rRay - 15,2*m_rRay*(1- ((double)AnthillFoodStock/MaxFoodStock)),7);
}


void Anthill::advance(int )
{
    // it doesn't move
}

bool Anthill::consumeFoodStock(int p_Unit)
{
    if (AnthillFoodStock -  p_Unit > 0)
    {
        AnthillFoodStock -= p_Unit;
        return true;
    }

    return false;

}

void Anthill::bringMeFood(int p_Unit)
{
    qDebug() << "debut  : " <<  AnthillFoodStock;
    if(AnthillFoodStock + p_Unit < MaxFoodStock )
    {
        AnthillFoodStock += p_Unit;
    }
    else
        AnthillFoodStock = MaxFoodStock;

    qDebug() << "fin  : " <<  AnthillFoodStock;
}


