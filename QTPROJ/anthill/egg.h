#ifndef EGG_H
#define EGG_H
#include "staticant.h"


class Egg: public StaticAnt
{
public:
    Egg();
    ~Egg();
    void EvolveToLarva();
protected:
    int RoundsToWait;
};

#endif // EGG_H
