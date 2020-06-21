#ifndef ANT_H
#define ANT_H

#include <QGraphicsItem>
#include <QGraphicsScene>

#include "anthill.h"


class Ant: public QGraphicsItem
{
public:
    bool m_bIsAQueen=false; //TODO : a setter
    Ant(Anthill* p_pAnthill);
    virtual ~Ant();

    void Die() {this->~Ant();}

    bool eatToSurvive();

    inline void takeDamage(const int damage) {m_iHealthPoints -= damage; if (m_iHealthPoints <=0) Die();}

    const Anthill* getAnthill() const {return m_pAnthillOwner;}

    // QGraphics Item
    virtual QRectF boundingRect() const override =0;
    virtual QPainterPath shape() const override =0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override =0;

protected:
    // Methods

    /*!
     * \brief advance
     * \param phase
     */
    virtual void advance(int phase) override = 0; // QGraphicsItem

    /*!
     * \brief setColors, SET THE FABULOUS COLORS
     * \param p_ColorAnthill
     * \param p_ColorAntType
     */
    virtual void setColors(const QColor& p_ColorAnthill, const QColor& p_ColorAntType) {colorAnthill = p_ColorAnthill; colorAntType = p_ColorAntType;}

    virtual void setScaleFactor(const qreal& p_ScaleFactor) {ScaleFactor = p_ScaleFactor;}

    // Member Values
    const int MaxHealthPoint = 1000;
    int m_iHealthPoints = MaxHealthPoint;
    Anthill* m_pAnthillOwner;
    qreal ScaleFactor;
    qreal angle = 0;
    const qreal MaxSpeed = -3;
    qreal speed = MaxSpeed;
    QColor colorAnthill;
    QColor colorAntType;
};

#endif // ANT_H
