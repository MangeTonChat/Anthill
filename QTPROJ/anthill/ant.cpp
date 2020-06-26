#include "ant.h"

Ant::Ant(Anthill* p_pAnthill) :m_pAnthillOwner(p_pAnthill)  , m_bIsAQueen(false)
{
    colorAnthill = p_pAnthill->getColor();
}

Ant::~Ant()
{

}

bool Ant::eatToSurvive()
{
    // If the ant can't eat, reduce its life
    if(!m_pAnthillOwner->consumeFoodStock(1))
    {
        m_iHealthPoints--;

        if (m_iHealthPoints < 0 ) // die if no more health
        {
            this->~Ant();
            return false;
        }
    }
    else if (m_iHealthPoints < MaxHealthPoint)
        m_iHealthPoints++;

    return true;

}

void Ant::takeDamage(const int damage)
{
    m_iHealthPoints -= damage;
    if (m_iHealthPoints <=0)
        Die();
}
