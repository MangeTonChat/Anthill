#ifndef MOVINGANT_H
#define MOVINGANT_H
#include "ant.h"


class MovingAnt: public Ant
{
public:
    MovingAnt(Anthill* p_pAnthill);
    virtual ~MovingAnt();

    /*!
     * \brief Attack , Pure Virtual
     * \param Enemy
     */
    virtual void Attack(MovingAnt* Enemy) = 0;

    // QGraphics Item Inherited Funtions

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:

    // Methods

    /*!
     * \brief advance , manage Attack and staying inside the anthill
     * \param phase
     */
    virtual void advance(int phase) override;

};

#endif // MOVINGANT_H
