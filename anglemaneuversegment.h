#ifndef ANGLEMANEUVERSEGMENT_H
#define ANGLEMANEUVERSEGMENT_H

#include "maneuversegment.h"
#include "planedirection.h"
#include <math.h>
#include <iostream>

class AngleManeuverSegment : public ManeuverSegment
{
public:
    static AngleManeuverSegment * getInstance(QDomElement segmentElement) {
     QDomElement startIndexElement = segmentElement.firstChildElement("start");
     QDomElement endIndexElement = segmentElement.firstChildElement("end");

     if (startIndexElement.isNull() ||
         startIndexElement.attribute("index").isNull() ||
         startIndexElement.attribute("index").isEmpty() ||
         endIndexElement.isNull() ||
         endIndexElement.attribute("index").isNull() ||
         endIndexElement.attribute("index").isEmpty()) {
         return NULL;
     }

     int startIndex = startIndexElement.attribute("index").toInt();
     int endIndex = startIndexElement.attribute("index").toInt();

     return new AngleManeuverSegment(startIndex, endIndex);
    }
    bool resolveReferences(QVector<ManeuverSegment *> directionSegments);

private:
    AngleManeuverSegment(int startIndex,
                         int endIndex);
    int startIndex;
    int endIndex;
};

#endif // ANGLEMANEUVERSEGMENT_H
