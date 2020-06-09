#include "ant.h"

Ant::Ant(Anthill* p_pAnthill) : m_pAnthillOwner(p_pAnthill)
{
    colorAnthill = p_pAnthill->getColor();
}

Ant::~Ant()
{

}
