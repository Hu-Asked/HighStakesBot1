#include "odometry.hpp"

void Odometry::update(double xPosition, double yPosition, double heading) {
    // yPosition is parallel to the heading of the robot
    double deltaX = xPosition - prevX;
    double deltaY = yPosition - prevY;
    double deltaHeading = heading - prevHeading;

    if (deltaX > 0.1) {  // placeholder
        bool isInterfered = true;
    }
    // deltaY = hyp, currentX = sin, currentY = cos
    currentX += deltaY * sin(heading);
    currentY += deltaY * cos(heading);

    prevX = xPosition;
    prevY = yPosition;
}

void Odometry::setInitialPosition(double x, double y, double heading) {
    currentX = x;
    currentY = y;
    prevX = x;
    prevY = y;
    prevHeading = heading;
}

double Odometry::getHeadingToTarget(double targetX, double targetY, double curHeading) {
    double deltaX = targetX - currentX;
    double deltaY = targetY - currentY;
    double angle = atan2(deltaX, deltaY) * 180 / M_PI;
    return angle - curHeading;
}

double Odometry::getDistanceToTarget(double targetX, double targetY) {
    double deltaX = targetX - currentX;
    double deltaY = targetY - currentY;
    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

double Odometry::getX() {
    return currentX;
}

double Odometry::getY() {
    return currentY;
}