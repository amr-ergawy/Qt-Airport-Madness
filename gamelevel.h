#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <QVector>
#include <QGraphicsView>

#include "runway.h"

class GameLevel
{
public:
    GameLevel(long newPlaneInterval, int maxNumberOfPlanes);
    void addRunWay(RunWay * runWay);
    long getNewPlaneInterval();
    int getMaxNumberOfPlanes();
    RunWay * getRunWay(int runWayIndex);

private:
    long newPlaneInterval;
    int maxNumberOfPlanes;
    QVector<RunWay *> runWays;

};

#endif // GAMELEVEL_H
