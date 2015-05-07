#include "runway.h"

RunWay::RunWay()
{
}

void RunWay::setDeparturePath(PlaneDirection * departure) {
    this->departure = departure;
}

void RunWay::setArrivalPath(PlaneDirection * arrival) {
    this->arrival = arrival;
}

PlaneDirection * RunWay::getDeparture()
{
    return this->departure;
}

PlaneDirection * RunWay::getArrival()
{
    return this->arrival;
}

RunWay::~RunWay()
{
    delete this->departure;
    delete this->arrival;
}
