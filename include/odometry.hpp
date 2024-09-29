#include "main.h"

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

class Odometry {
   public:
    Odometry(pros::Rotation parallel, pros::Rotation perpendicular);
    void reset();
    void update(double heading);
    void setInitialPosition(double x, double y, double heading);
    pros::Rotation parallel;
    pros::Rotation perpendicular;
    double getHeadingToTarget(double targetX, double targetY, double curHeading);
    double getDistanceToTarget(double targetX, double targetY);
    double getX();
    double getY();
    double currentX = 0;
    double currentY = 0;
    double prevX = 0;
    double prevY = 0;
    double prevHeading = 0;
};

#endif  // ODOMETRY_HPP