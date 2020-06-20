#ifndef ANT_H
#define ANT_H

#include <QGraphicsItem>

#include "anthill.h"


class Ant: public QGraphicsItem
{
public:
    Ant(Anthill* p_pAnthill);
    virtual ~Ant();

    void Die() {this->~Ant();}

    bool eatToSurvive();



    const Anthill* getAnthill() const {return m_pAnthillOwner;}

    // QGraphics Item
    virtual QRectF boundingRect() const override =0;
    virtual QPainterPath shape() const override =0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override =0;

protected:
    // Methods
    virtual void advance(int phase) override = 0; // QGraphicsItem

    virtual void setColors(const QColor& p_ColorAnthill, const QColor& p_ColorAntType) {colorAnthill = p_ColorAnthill; colorAntType = p_ColorAntType;}
    virtual void setScaleFactor(const qreal& p_ScaleFactor) {ScaleFactor = p_ScaleFactor;}

    // Member Values
    const int MaxHealthPoint = 1000;
    int m_iHealthPoints = MaxHealthPoint;
    bool m_bIsAQueen;
    Anthill* m_pAnthillOwner;
    qreal ScaleFactor;
    qreal angle = 0;
    const qreal MaxSpeed = -3;
    qreal speed = MaxSpeed;
    QColor colorAnthill;
    QColor colorAntType;
};

#endif // ANT_H
