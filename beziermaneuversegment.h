#ifndef BEZIERMANEUVERSEGMENT_H
#define BEZIERMANEUVERSEGMENT_H

#include <QPoint>

#include "maneuversegment.h"
#include "planedirection.h"
#include "beziermaneuveranimation.h"

class BezierManeuverSegment : public ManeuverSegment
{
public:
    static BezierManeuverSegment * getInstance(QDomElement segmentElement) {
     QDomElement startPointElement = segmentElement.firstChildElement("start");
     QDomElement keyPointElement1 = segmentElement.firstChildElement("key1");
     QDomElement keyPointElement2 = segmentElement.firstChildElement("key2");
     QDomElement endPointElement = segmentElement.firstChildElement("end");

     if (startPointElement.isNull() ||
         startPointElement.attribute("x").isNull() ||
         startPointElement.attribute("x").isEmpty() ||
         startPointElement.attribute("y").isNull() ||
         startPointElement.attribute("y").isEmpty() ||
         keyPointElement1.isNull() ||
         keyPointElement1.attribute("x").isNull() ||
         keyPointElement1.attribute("x").isEmpty() ||
         keyPointElement1.attribute("y").isNull() ||
         keyPointElement1.attribute("y").isEmpty() ||
         keyPointElement2.isNull() ||
         keyPointElement2.attribute("x").isNull() ||
         keyPointElement2.attribute("x").isEmpty() ||
         keyPointElement2.attribute("y").isNull() ||
         keyPointElement2.attribute("y").isEmpty() ||
         endPointElement.isNull() ||
         endPointElement.attribute("x").isNull() ||
         endPointElement.attribute("x").isEmpty() ||
         endPointElement.attribute("y").isNull() ||
         endPointElement.attribute("y").isEmpty()) {
         return NULL;
     }

     QPoint * start = new QPoint(startPointElement.attribute("x").toInt(),
                                 startPointElement.attribute("y").toInt());
     QPoint * key1 = new QPoint(keyPointElement1.attribute("x").toInt(),
                               keyPointElement1.attribute("y").toInt());
     QPoint * key2 = new QPoint(keyPointElement2.attribute("x").toInt(),
                               keyPointElement2.attribute("y").toInt());
     QPoint * end = new QPoint(endPointElement.attribute("x").toInt(),
                               endPointElement.attribute("y").toInt());

     return new BezierManeuverSegment(start, key1, key2, end);
    }
    QLine * firstLine();
    QPropertyAnimation * animation();

    ~BezierManeuverSegment();

private:
    BezierManeuverSegment(QPoint * start,
                          QPoint * key1,
                          QPoint * key2,
                          QPoint * end);
    QPoint * start;
    QPoint * key1;
    QPoint * key2;
    QPoint * end;
};

#endif // BEZIERMANEUVERSEGMENT_H
