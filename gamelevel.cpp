#include "gamelevel.h"

GameLevel::GameLevel(long newPlaneInterval, int maxNumberOfPlanes)
{
    this->newPlaneInterval = newPlaneInterval;
    this->maxNumberOfPlanes = maxNumberOfPlanes;
}

void GameLevel::addRunWay(RunWay * runWay)
{
    this->runWays.append(runWay);
}

long GameLevel::getNewPlaneInterval()
{
    return this->newPlaneInterval;
}

int GameLevel::getMaxNumberOfPlanes()
{
    return this->maxNumberOfPlanes;
}

RunWay * GameLevel::getRunWay(int runWayIndex)
{
    return this->runWays.at(runWayIndex);
}
