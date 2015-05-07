#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QMap>

#include <QtGlobal>
#include <iostream>

#include "levelmanager.h"
#include "planemodel.h"
#include "plane.h"
#include "pilot.h"
#include "takeoffpilot.h"
#include "landingpilot.h"

class GameEngine : public QObject
{
Q_OBJECT

public:
    static GameEngine *instance (int numOfLevels=0)
    {
        if (m_instance == 0)
          m_instance = new GameEngine(numOfLevels);
        return (m_instance);
    }

    bool startNextLevel();

    ~GameEngine ()
    {
        m_instance = 0;
    }

public slots:
    void addNewPlane();

    //Adding slots for interesting pilot events
    //E.g. takeoff pilot taxing, landing pilot landing, ... etc
    void takeOffPilotFinished(Pilot* pilot, Plane * plane);
    void landingPilotFinished(Pilot* pilot, Plane * plane);

    void movingPlane();
private:
    GameEngine(int numOfLevels)
    {
        this->numOfLevels = numOfLevels;
    }    

    static GameEngine *m_instance;
    static int currentLevelIndex;
    static int numOfLevels;
    static QTimer addNewPlaneTimer;
    static int maxNumberOfPlanes;
    static int numOfPlanesInScene;

    QMap<QTime, Plane *> timesToPlanes;
    QMap<QTime, Pilot *> timesToPilots;
    void registerCreationTime(Pilot * pilot, Plane * plane);
    void unregisterCreationTime(Plane * plane);
};

#endif // GAMEENGINE_H
