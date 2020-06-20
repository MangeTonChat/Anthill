#include "larva.h"
#include "worker.h"

#include <QtWidgets>

Larva::Larva(Anthill* p_pAnthill) : StaticAnt(p_pAnthill)
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.25; // larva is tiny

    colorAntType = QColor(Qt::yellow);

    timer.start();
}

void Larva::advance(int step){

    if (!step)
        return;

    if(timer.elapsed()>TimeLarvaWaitsToEvolve){
        Ant *worker = new Worker(m_pAnthillOwner);
        if(m_bIsAQueen==true){
            worker->m_bIsAQueen=true;
        }
        worker->setPos(mapToScene(QPointF(0,0)));
        scene()->addItem(worker);
        Die();
    }
}

void Larva::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body below
    painter->setBrush(colorAnthill);
    painter->drawEllipse(-15*ScaleFactor, 15*ScaleFactor, 30*ScaleFactor, 40*ScaleFactor);

    // Body Middle
    painter->setBrush(colorAntType);
    painter->drawEllipse(-10*ScaleFactor, -15*ScaleFactor, 20*ScaleFactor, 30*ScaleFactor);

    // Head
    painter->setBrush(colorAntType);
    painter->drawEllipse(-10*ScaleFactor, -35*ScaleFactor, 20*ScaleFactor, 20*ScaleFactor);

    // Eyes
    painter->setBrush(Qt::black);
    painter->drawEllipse(-9*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);
    painter->drawEllipse(1*ScaleFactor, -38*ScaleFactor, 8*ScaleFactor, 8*ScaleFactor);
}

