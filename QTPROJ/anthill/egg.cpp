#include <QtWidgets>

#include "egg.h"
#include "larva.h"

Egg::Egg(Anthill* p_pAnthill) : StaticAnt(p_pAnthill)
 {
    ScaleFactor = 0.5;
    PixEgg = QPixmap(":/images/egg.png");
    PixEgg = PixEgg.scaled(30,30);
    timer.start();
 }

void Egg::advance(int step){

    if (!step)
        return;

    if(timer.elapsed()>TimeEggWaitsToEvolve){
        Ant *larva = new Larva(m_pAnthillOwner);
        if(m_bIsAQueen==true){
            larva->m_bIsAQueen=true;
        }
        larva->setPos(mapToScene(QPointF(0,0)));
        scene()->addItem(larva);
        Die();
    }
}

void Egg::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,PixEgg);
}
