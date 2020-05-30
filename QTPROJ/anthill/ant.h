#ifndef ANT_H
#define ANT_H
#include <QGraphicsItem>


class Ant: public QGraphicsItem
{
public:
    Ant();
    ~Ant();
    void Die();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;
protected:
    int HealthPoints;
    bool isAQueen;
};

#endif // ANT_H
