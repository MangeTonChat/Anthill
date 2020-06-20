#include "map.h"

void Map::Generate(){

    //External border construction
    QPixmap Cobble = QPixmap(":/images/stone_bricks.png");

    int WidthCobble = Cobble.width()/2;

    //Two horizontal limits
    for(int x=-Scene->width()/2; x<Scene->width()/2-WidthCobble; x+=WidthCobble)
    {
        Obstacle* border=new Obstacle(Cobble);
        border->setScale(0.5);
        border->setPos(x,-Scene->height()/2);
        Scene->addItem(border);
        Obstacle* border2=new Obstacle(Cobble);
        border2->setScale(0.5);
        border2->setPos(x,Scene->height()/2-WidthCobble);
        Scene->addItem(border2);
    }

    //Two vertical limits
    for(int y=-Scene->width()/2; y<Scene->height()/2-WidthCobble; y+=WidthCobble)
    {
        Obstacle* border=new Obstacle(Cobble);
        border->setScale(0.5);
        border->setPos(-Scene->width()/2,y);
        Scene->addItem(border);
        Obstacle* border2=new Obstacle(Cobble);
        border2->setScale(0.5);
        border2->setPos(Scene->width()/2-WidthCobble,y);
        Scene->addItem(border2);
    }


    //Last cobble to complete the map
    Obstacle* border=new Obstacle(Cobble);
    border->setScale(0.5);
    border->setPos(Scene->width()/2-WidthCobble,Scene->height()/2-WidthCobble);
    Scene->addItem(border);
}

Map::~Map(){

}
