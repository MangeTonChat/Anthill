#ifndef ANT_H
#define ANT_H
#include <QGraphicsItem>


class Ant: public QGraphicsItem
{
public:
    Ant();
    Ant(const QColor& p_ColorAnthill) {colorAnthill = p_ColorAnthill;}
    virtual ~Ant();

    void Die();

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
    int m_iHealthPoints;
    bool m_bIsAQueen;
    qreal ScaleFactor;
    qreal angle = 0;
    qreal speed = 0;
    QColor colorAnthill;
    QColor colorAntType;
};

#endif // ANT_H
