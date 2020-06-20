#include <QtMath>
#include <QtWidgets>
#include <QRandomGenerator>
#include <QDebug>

#include "ant.h"
#include "queen.h"
#include "warrior.h"
#include "map.h"
#include "worker.h"
#include "anthill.h"
#include "view.h"
#include "Beef.h"
#include "obstacle.h"


static constexpr int    AnthillCount            = 1;
static constexpr int    AnthillRay              = 100;
static constexpr int    AntCount                = 20;
static constexpr int    BorderLength            = 1000 ; // Scene size , it's a square
static constexpr double PercentageOfBeef        = 10 ; //  %

// Obstacle
static constexpr double PercentageOfObstacle    = 70 ; // %
static constexpr int    PercentageOfWall        = 90; // percent of continuous walls
static constexpr int    WallMinLength           = 3;
static constexpr int    WallMaxLength           = 20;



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-BorderLength, -BorderLength, 2*BorderLength, 2*BorderLength);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Map Carte(&scene);
    Carte.Generate();

    // needed
    int WidthCobble = (QPixmap(":/images/cobblestone.png").width()/2);

    // Avoid Anthill creation in the border
    int SpaceToGenerate = BorderLength - WidthCobble + 3 - AnthillRay;

    // Init anthills
    for (int i = 0; i < AnthillCount; ++i)
    {
        // Generate random color and coord
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        QColor colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256));

        // Create Anthill
        Anthill *anthill= new Anthill(qreal(AnthillRay),colorAnthill);
        anthill->setPos(x,y);
        scene.addItem(anthill);

        // avoid anthill superposition
        if(!scene.collidingItems(anthill).isEmpty())
        {
            i--;
            delete anthill;
        }
        // If the space is free, create the anthill
        else
        {
            // Create Queen
            Ant *queen = new Queen(anthill);
            queen->setPos(x ,y);
            scene.addItem(queen);

            // Create worker
            for (int i = 0; i < AntCount; ++i) // antCount
            {
                // Generate ant in the anthill
                double angleRandom = QRandomGenerator::global()->bounded(0,628) / 100.0;
                int rayRandom = QRandomGenerator::global()->bounded(0,anthill->getRay());
                Ant *antWorker = new Worker(anthill);
                antWorker->setPos(x + rayRandom*std::cos(angleRandom) , y + rayRandom*std::sin(angleRandom));
                scene.addItem(antWorker);
            }

            // Create Warrior
            for (int i = 0; i < AntCount; ++i)
            {
                // Generate ant in the anthill
                double angleRandom = QRandomGenerator::global()->bounded(0,628) / 100.0;
                int rayRandom = QRandomGenerator::global()->bounded(0,anthill->getRay());
                Ant *antWarrior = new Warrior(anthill);
                antWarrior->setPos(x + rayRandom*std::cos(angleRandom) , y + rayRandom*std::sin(angleRandom));
                scene.addItem(antWarrior);
            }
        }
    }

    //Generate some random obstacles
    QPixmap l_Obstacle = QPixmap(":/images/cobblestone.png");
    SpaceToGenerate = BorderLength - WidthCobble - l_Obstacle.width()/2;

    // Compute number of obstacle wanted
    int l_iObstacleNumber = (std::pow(BorderLength,2)*(PercentageOfObstacle/100)) / std::pow(l_Obstacle.width()/2,2) ;

    for(double i = l_iObstacleNumber ; i>0 ; i--)
    {

        Obstacle* randomObstacle = new Obstacle(l_Obstacle);
        randomObstacle->setScale(0.5);

        // Random position
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomObstacle->setPos(x,y);
        scene.addItem(randomObstacle);

        // Avoid superposition of obstacle
        if(!scene.collidingItems(randomObstacle).isEmpty())
        {
            i++;
            delete randomObstacle;
        }
        // Create the wall
        else
        {
            //We need to build a wall , PercentageOfWall chances of wall creation
            if(QRandomGenerator::global()->bounded(0,100)<=PercentageOfWall)
            {
                int wallLength = QRandomGenerator::global()->bounded(WallMinLength,WallMaxLength); // random length
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
                    scene.addItem(newWall);

                    // Avoid object superposition and wall creation outside the scene
                    if(!scene.collidingItems(newWall).isEmpty()||qFabs(newWall->pos().x())>SpaceToGenerate||qFabs(newWall->pos().y())>SpaceToGenerate)
                    {
                        i++;
                        delete newWall;
                    }
                }
                i-=wallLength-1; // decrement with the number of obstacle created
            }
        }
    }

    //Generate some random bouffe
    QPixmap BeefPixmap = QPixmap(":/images/beef.png");
    SpaceToGenerate = BorderLength - WidthCobble - BeefPixmap.width()/2;

    // Compute number of beef wanted
    int l_iBeefNumber = (std::pow(BorderLength,2)*(PercentageOfBeef/100)) / std::pow(BeefPixmap.width()/2,2) ;

    for(double i=l_iBeefNumber; i>0; i--)
    {
        Beef* randomBeef=new Beef(BeefPixmap);
        randomBeef->setScale(0.5);

        // Random Position
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomBeef->setPos(x,y);
        scene.addItem(randomBeef);

        //No superposition allowed
        if(!scene.collidingItems(randomBeef).isEmpty()) {
            i++;
            delete randomBeef;
        }
    }

    // Set View and background
    View view;
    view.setScene(&scene);

    // Set Title and init window size
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sweaty Anthill"));
    view.showMaximized();

    // Set FPS
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);
    //timer.start(1000 / 10);

    return app.exec();
}
