#ifndef TAKEOFFPILOT_H
#define TAKEOFFPILOT_H

#include "pilot.h"

class TakeOffPilot : public Pilot
{
Q_OBJECT

public:
    TakeOffPilot(Plane * plane, PlaneDirection * planeDirection);
    void startNextManeuver();

public slots:
    void maneuverFinished();
    bool processCommand(QAction * action);

private:
    int lastScheduledIndex;
    int currentCommandIndex;

    QMap<int, QSequentialAnimationGroup *> scheduledManeuvers;
    QMap<int, QSequentialAnimationGroup *> suspendedManeuvers;
};

#endif // TAKEOFFPILOT_H
