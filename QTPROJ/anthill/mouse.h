#ifndef MOUSE_H
#define MOUSE_H
#include <cmath>
#include <QGraphicsItem>

class Mouse : public QGraphicsItem
{
public:
    Mouse();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;

};

#endif // MOUSE_H
