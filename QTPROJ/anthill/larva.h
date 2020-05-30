#ifndef LARVA_H
#define LARVA_H
#include "staticant.h"


class Larva: public StaticAnt
{
public:
    Larva();
    ~Larva();
    void EvolveToWorker();
protected:
    int RoundsToWait;
};

#endif // LARVA_H
