#ifndef LINEMANEUVERANIMATION_H
#define LINEMANEUVERANIMATION_H

#include <QtCore/qpropertyanimation.h>
#include <iostream>

class LineManeuverAnimation : public QPropertyAnimation
{
public:
    LineManeuverAnimation();
    void updateCurrentTime(int currentTime);
};

#endif // LINEMANEUVERANIMATION_H
