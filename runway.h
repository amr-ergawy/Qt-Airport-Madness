#ifndef RUNWAY_H
#define RUNWAY_H

#include "planedirection.h"

class RunWay
{
public:
    RunWay();
    void setDeparturePath(PlaneDirection * departure);
    void setArrivalPath(PlaneDirection * arrival);
    PlaneDirection * getDeparture();
    PlaneDirection * getArrival();
    ~RunWay();

private:
    PlaneDirection * departure;
    PlaneDirection * arrival;
};

#endif // RUNWAY_H
