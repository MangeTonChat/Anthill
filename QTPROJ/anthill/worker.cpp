#include "worker.h"


Worker::Worker(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.3;

    colorAntType = QColor(Qt::green);

    timer.start();

}

void Worker::Attack(MovingAnt* Enemy)
{
    Enemy->takeDamage(QRandomGenerator::global()->bounded(5));
}

void Worker::advance(int step){

    if (!step)
        return;

    MovingAnt::advance(step);

    if(timer.elapsed()>TimeWorkerWaitsToEvolve){
        if(m_bIsAQueen==true){
            EvolveToQueen();
            Die();
        }
        else {
            EvolveToWarrior();
            Die();
        }
    }
}

void Worker::EvolveToQueen(){
    Ant *queen = new Queen(m_pAnthillOwner);
    queen->m_bIsAQueen=true; //To know this one is supposed to gtfo one day
    queen->setPos(mapToScene(QPointF(0,0)));
    scene()->addItem(queen);
}

void Worker::EvolveToWarrior(){
    Ant *warrior = new Warrior(m_pAnthillOwner);
    warrior->m_bIsAQueen=true; //To know this one is supposed to gtfo one day
    warrior->setPos(mapToScene(QPointF(0,0)));
    scene()->addItem(warrior);
}
