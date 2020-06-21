#include "map.h"

void Map::Generate(const int p_BorderSize, const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength, const double p_FoodPercentage )
{
    m_iBorderSize = p_BorderSize;

    GenerateBorder();

    GenerateObstacle(p_ObstaclePercentage, p_PercentageOfWall,  p_MaxWallLength,  p_MinWallLength);

    GenerateFood(p_FoodPercentage);
}

Map::~Map(){

}

void Map::GenerateBorder()
{
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

void Map::GenerateObstacle(const double p_ObstaclePercentage, const int p_PercentageOfWall, const int p_MaxWallLength, const int p_MinWallLength)
{
    // needed
    int WidthCobble = (QPixmap(":/images/cobblestone.png").width()/2);

    //Generate some random obstacles

    QPixmap l_Obstacle = QPixmap(":/images/cobblestone.png");
    int SpaceToGenerate = m_iBorderSize - WidthCobble - l_Obstacle.width()/2;
    //SpaceToGenerate = BorderLength - Obstacle.width()/2;

    // Compute number of obstacle wanted
    int l_iObstacleNumber = (std::pow(m_iBorderSize,2)*(p_ObstaclePercentage/100)) / std::pow(l_Obstacle.width()/2,2) ;

    for(double i = l_iObstacleNumber ; i>0 ; i--)
    {

        Obstacle* randomObstacle = new Obstacle(l_Obstacle);
        randomObstacle->setScale(0.5);

        // Random position
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomObstacle->setPos(x,y);
        Scene->addItem(randomObstacle);

        // Avoid superposition of obstacle
        if(!Scene->collidingItems(randomObstacle).isEmpty())
        {
            i++;
            delete randomObstacle;
        }
        // Create the wall
        else
        {
            //We need to build a wall , PercentageOfWall chances of wall creation
            if(QRandomGenerator::global()->bounded(0,100)<=p_PercentageOfWall)
            {
                int wallLength = QRandomGenerator::global()->bounded(p_MinWallLength,p_MaxWallLength); // random length
                for(int j=0;j<wallLength;j++)
                {
                    Obstacle* newWall = new Obstacle(l_Obstacle);
                    newWall->setScale(0.5);

                    int direction = QRandomGenerator::global()->bounded(0,3); // Random direction

                    if(direction==0)
                        x=x+WidthCobble;

                    else if(direction==1)
                        y=y-WidthCobble;

                    else if(direction==2)
                        x=x-WidthCobble;

                    else // direction = 3
                        y=y+WidthCobble;

                    newWall->setPos(x,y);
                    Scene->addItem(newWall);

                    // Avoid object superposition and wall creation outside the scene
                    if(!Scene->collidingItems(newWall).isEmpty()||qFabs(newWall->pos().x())>SpaceToGenerate||qFabs(newWall->pos().y())>SpaceToGenerate)
                    {
                        i++;
                        delete newWall;
                    }
                }
                i-=wallLength-1; // decrement with the number of obstacle created
            }
        }
    }
}

void Map::GenerateFood(const double p_FoodPercentage)
{
    // needed
    int WidthCobble = (QPixmap(":/images/cobblestone.png").width()/2);

    //Generate some random bouffe
    QPixmap BeefPixmap = QPixmap(":/images/beef.png");
    int SpaceToGenerate = m_iBorderSize - WidthCobble - BeefPixmap.width()/2;
     //SpaceToGenerate = BorderLength - BeefPixmap.width()/2;

    // Compute number of beef wanted
    int l_iBeefNumber = (std::pow(m_iBorderSize,2)*(p_FoodPercentage/100)) / std::pow(BeefPixmap.width()/2,2) ;

    for(double i=l_iBeefNumber; i>0; i--)
    {
        Beef* randomBeef=new Beef(BeefPixmap);
        randomBeef->setScale(0.5);

        // Random Position
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomBeef->setPos(x,y);
        Scene->addItem(randomBeef);

        //No superposition allowed
        if(!Scene->collidingItems(randomBeef).isEmpty())
        {
            i++;
            delete randomBeef;
        }
        else
        {
            // Dynamic Regeneration
            QObject::connect(randomBeef, SIGNAL(destroyed(QObject*)),this, SLOT(RegenerateFood(QObject*)));
        }
    }
}

void Map::RegenerateFood(QObject*)
{
    //qDebug() << " Regenerate DA SHIT " ;
    // needed
    int WidthCobble = (QPixmap(":/images/cobblestone.png").width()/2);


    //Generate some random bouffe
    QPixmap BeefPixmap = QPixmap(":/images/beef.png");

    int SpaceToGenerate = m_iBorderSize - WidthCobble - BeefPixmap.width()/2;

    Beef* randomBeef=new Beef(BeefPixmap);
    randomBeef->setScale(0.5);
    Scene->addItem(randomBeef);

    int x , y;

    do{
        // Random Position
        x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomBeef->setPos(x,y);

    } while(!Scene->collidingItems(randomBeef).isEmpty());

    // Dynamic Regeneration
    QObject::connect(randomBeef, SIGNAL(destroyed(QObject*)),this, SLOT(RegenerateFood(QObject*)));
}
