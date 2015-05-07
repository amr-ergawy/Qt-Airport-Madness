#ifndef MANEUVERSEGMENT_H
#define MANEUVERSEGMENT_H

#include <QObject>
#include <QLine>
#include <QVector>
#include <QPropertyAnimation>
#include <QDomElement>
#include <QEasingCurve>

#include <iostream>

class ManeuverSegment : public QObject
{
    Q_OBJECT
public:
   static ManeuverSegment * getInstance(QDomElement segmentElement) {
       if (segmentElement.isNull()) {
           //TODO: Log error messages
       }
    return NULL;
   }
   virtual QLine * firstLine();
   virtual QLine * lastLine();
   virtual bool resolveReferences(QVector<ManeuverSegment *> directionSegment);
   virtual QPropertyAnimation * animation();
   ~ManeuverSegment();

protected:
   ManeuverSegment();
};

#endif // MANEUVERSEGMENT_H
