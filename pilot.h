#ifndef PILOT_H
#define PILOT_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QAction>
#include <QSequentialAnimationGroup>
#include <QGraphicsTextItem>
#include <QAbstractAnimation>
#include <QGraphicsProxyWidget>
#include <QMenu>

#include <iostream>

#include "plane.h"
#include "planedirection.h"
#include "levelmanager.h"

class Pilot : public QObject
{
Q_OBJECT

public:
    Pilot(Plane * plane, PlaneDirection * planeDirection);
    virtual void takeControl();
    virtual int currentManueverCollisionDegree();
    virtual void handlePlaneCollision();
    virtual void handlePlaneStopping();

public slots:
    void maneuverFinished();
    virtual bool processCommand(QAction * action);

signals:
    void pilotFinished(Pilot * pilot, Plane * plane);

protected:
    virtual void initPlane();
    virtual void cleanAfterPlane();

    QMenu * commandMenu;
    QGraphicsProxyWidget * commandMenuProxy;
    Plane * plane;
    PlaneDirection * planeDirection;
    QSequentialAnimationGroup * currentManeuver;

    // TODO: combine these structures somehow
    QVector<QString> commandsList;
    QMap<QString, int> maneuversToCollisionDegree;
    QMap<QString, bool> maneuversToStoppable;

    // Eleminate map lookup time from the collision handling context
    int currentCollisionDegree;
    int currentStoppableFlag;
};

#endif // PILOT_H
