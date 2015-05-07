#ifndef BEZIERMANEUVERANIMATION_H
#define BEZIERMANEUVERANIMATION_H

#include <QtCore/qpropertyanimation.h>
#include <QPainterPath>
#include <iostream>

class BezierManeuverAnimation : public QPropertyAnimation
{
public:
    BezierManeuverAnimation(QPoint * start, QPoint * key1,
                            QPoint * key2, QPoint * end);
    void updateCurrentTime(int currentTime);

private:
    QPainterPath path;
};

#endif // BEZIERMANEUVERANIMATION_H
