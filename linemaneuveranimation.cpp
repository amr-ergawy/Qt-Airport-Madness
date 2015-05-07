#include "linemaneuveranimation.h"

LineManeuverAnimation::LineManeuverAnimation()
{
}

void LineManeuverAnimation::updateCurrentTime(int currentTime)
{
    /*std::cout << "Line anmiation passing over received update-current-time: "
              << currentTime
              << std::endl;*/
    QPropertyAnimation::updateCurrentTime(currentTime);
}
