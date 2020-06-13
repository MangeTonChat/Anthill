#include "ant.h"

Ant::Ant(Anthill* p_pAnthill) : m_pAnthillOwner(p_pAnthill)
{
    colorAnthill = p_pAnthill->getColor();
}

Ant::~Ant()
{

}

bool Ant::eatToSurvive()
{
    // If the ant can't eat, reduce its life
    if(!m_pAnthillOwner->consumeFoodStock(1)) // a 1 stp
    {
        m_iHealthPoints--;

        if (m_iHealthPoints < 0 ) // die if no more health
        {
            this->~Ant();
            return false;
        }
    }

    return true;

}
