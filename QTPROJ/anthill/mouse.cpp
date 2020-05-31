#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;
constexpr qreal ScaleFactor = 0.2;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

//! [0]
Mouse::Mouse() : color(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256))
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}
//! [0]

//! [1]
QRectF Mouse::boundingRect() const
{
    /*qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);*/
    qreal adjust = 3.5;
        return QRectF(-35*ScaleFactor - adjust, -55*ScaleFactor - adjust,
                      70*ScaleFactor + adjust, 110*ScaleFactor + adjust);
}
//! [1]

//! [2]
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-35*ScaleFactor, -55*ScaleFactor, 70*ScaleFactor, 100*ScaleFactor);
    return path;
}
//! [2]

//! [3]
void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Pates arrière droite
    QPainterPath pathAD(QPointF(-5*ScaleFactor, 13*ScaleFactor));
    pathAD.cubicTo(-5*ScaleFactor, 13*ScaleFactor, -30*ScaleFactor, 25*ScaleFactor, -35*ScaleFactor, +55*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAD);

    // Pates arrière gauche
    QPainterPath pathAG(QPointF(5*ScaleFactor, 13*ScaleFactor));
    pathAG.cubicTo(5*ScaleFactor, 13*ScaleFactor, 30*ScaleFactor, 25*ScaleFactor, 35*ScaleFactor, 55*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAG);

    // Pates mid droite
    QPainterPath pathMD(QPointF(-8*ScaleFactor, 5*ScaleFactor));
    pathMD.cubicTo(-8*ScaleFactor, 5*ScaleFactor, -20*ScaleFactor, 2*ScaleFactor, -35*ScaleFactor, -10*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathMD);

    // Pates mid gauche
    QPainterPath pathMG(QPointF(8*ScaleFactor, 5*ScaleFactor));
    pathMG.cubicTo(8*ScaleFactor, 5*ScaleFactor, 20*ScaleFactor, 2*ScaleFactor, 35*ScaleFactor, -10*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathMG);

    // Pates avant droite
    QPainterPath pathAvD(QPointF(-8*ScaleFactor, -10*ScaleFactor));
    pathAvD.cubicTo(-8*ScaleFactor, -10*ScaleFactor, -20*ScaleFactor, -7*ScaleFactor, -35*ScaleFactor, -30*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAvD);

    // Pates avant gauche
    QPainterPath pathAvG(QPointF(-8*ScaleFactor, -10*ScaleFactor));
    pathAvG.cubicTo(8*ScaleFactor, -10*ScaleFactor, 20*ScaleFactor, -7*ScaleFactor, 35*ScaleFactor, -30*ScaleFactor);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathAvG);

    // Body below
    painter->setBrush(color);
    painter->drawEllipse(-15*ScaleFactor, 15*ScaleFactor, 30*ScaleFactor, 40*ScaleFactor);

    // Body Middle
    painter->setBrush(color);
    painter->drawEllipse(-10*ScaleFactor, -15*ScaleFactor, 20*ScaleFactor, 30*ScaleFactor);

    // Head
    painter->setBrush(color);
    painter->drawEllipse(-10*ScaleFactor, -35*ScaleFactor, 20*ScaleFactor, 20*ScaleFactor);

    // Eyes
    painter->setBrush(Qt::black);
    painter->drawEllipse(-9*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);
    painter->drawEllipse(1*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);



    // Pupils
    //painter->drawEllipse(QRectF(-5.0 + mouseEyeDirection, 30, 4, 4));
   // painter->drawEllipse(QRectF(5.0 + mouseEyeDirection, 30, 4, 4));

    /*// Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);*/
}
//! [3]

//! [4]
void Mouse::advance(int step)
{
    if (!step)
        return;
//! [4]
    // Don't move too far away
//! [5]
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
//! [5] //! [6]
    }
//! [6]

    // Try not to crash with any other mice
//! [7]
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                           << mapToScene(0, 0)
                           << mapToScene(-30, -50)
                           << mapToScene(30, -50));

    for (const QGraphicsItem *item : dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
//! [7] //! [8]
        }
//! [8] //! [9]
    }
//! [9]

    // Add some random movement
//! [10]
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }
//! [10]

//! [11]
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;
    speed = - speed;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
//! [11]
