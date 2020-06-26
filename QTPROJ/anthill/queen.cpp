#include "queen.h"


static constexpr int PercentageOfLay = 100;
static constexpr int OddsOfLayingQueen = -1;
static constexpr int TimeToWaitBeforeLaying = 2500;
static constexpr int FoodConsumptionToLay = 1;


Queen::Queen(Anthill* p_pAnthill) : MovingAnt(p_pAnthill)
{
    // randomly set first rotation and color
    setRotation(QRandomGenerator::global()->bounded(360 * 16));

    ScaleFactor = 0.5; // queen is bigger

    colorAntType = QColor(Qt::blue);

    //To indicate this queen won't migrate
    m_bIsAQueen=false;

    timer.start();
}

void Queen::Attack(MovingAnt* Enemy)
{
    Enemy->takeDamage(QRandomGenerator::global()->bounded(20,25));
}


void Queen::advance(int step)
{
    if (!step)
        return;

    MovingAnt::advance(step);

    if(timer.elapsed()>TimeToWaitBeforeLaying){
        if(m_pAnthillOwner->canLayEgg()){
            LayEgg();
        }
        timer.restart();
    }
}

void Queen::LayEgg()
{
    if(QRandomGenerator::global()->bounded(0,100)<=PercentageOfLay)
    {
        if(m_pAnthillOwner->consumeFoodStock((FoodConsumptionToLay/100)*m_pAnthillOwner->getMaxFoodStock()))
        {
            Ant *egg = new Egg(m_pAnthillOwner);
            if(QRandomGenerator::global()->bounded(0,100)<=OddsOfLayingQueen)
            {
                egg->setIsQueen(true);
            }
            egg->setPos(mapToScene(QPointF(0,0)));
            scene()->addItem(egg);
        }
    }
}
