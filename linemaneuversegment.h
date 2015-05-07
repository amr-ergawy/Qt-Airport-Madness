#ifndef LINEMANEUVERSEGMENT_H
#define LINEMANEUVERSEGMENT_H

#include <QPoint>

#include "maneuversegment.h"
#include "planedirection.h"
#include "linemaneuveranimation.h"

class LineManeuverSegment : public ManeuverSegment
{
public:
    static LineManeuverSegment * getInstance(QDomElement segmentElement) {
     QDomElement startPointElement = segmentElement.firstChildElement("start");
     QDomElement endPointElement = segmentElement.firstChildElement("end");

     if (startPointElement.isNull() ||
         startPointElement.attribute("x").isNull() ||
         startPointElement.attribute("x").isEmpty() ||
         startPointElement.attribute("y").isNull() ||
         startPointElement.attribute("y").isEmpty() ||
         endPointElement.isNull() ||
         endPointElement.attribute("x").isNull() ||
         endPointElement.attribute("x").isEmpty() ||
         endPointElement.attribute("y").isNull() ||
         endPointElement.attribute("y").isEmpty()) {
         return NULL;
     }

     QPoint * start = new QPoint(startPointElement.attribute("x").toInt(),
                                 startPointElement.attribute("y").toInt());
     QPoint * end = new QPoint(endPointElement.attribute("x").toInt(),
                               endPointElement.attribute("y").toInt());

     return new LineManeuverSegment(start, end);
    }
    QLine * firstLine();
    QLine * lastLine();
    QPropertyAnimation * animation();

    ~LineManeuverSegment();

private:
    LineManeuverSegment(QPoint * start,
                        QPoint * end);
    QLine * line;
};

#endif // LINEMANEUVERSEGMENT_H
