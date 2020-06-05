#ifndef ANT_H
#define ANT_H
#include <QGraphicsItem>


class Ant: public QGraphicsItem
{
public:
    Ant();
    Ant(QColor p_Color) : color(p_Color) {}
    virtual ~Ant();

    void Die();
    virtual QRectF boundingRect() const override =0;
    virtual QPainterPath shape() const override =0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override =0;

protected:
    // Methods
    virtual void advance(int phase) override = 0;

    // Member Values
    int m_iHealthPoints;
    bool m_bIsAQueen;
    qreal angle = 0;
    qreal speed = 0;
    QColor color;
};

#endif // ANT_H
