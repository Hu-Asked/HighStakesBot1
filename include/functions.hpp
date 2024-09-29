#include "main.h"
#include <cmath>

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

double updateRelativeHeading(double initialImuHeading, double currentImuHeading);
void drive(double target, double power, bool decelerateAtEnd);
void drive(double target, double power, bool decelerateAtEnd, std::function<void()> customFunction, double positionToCall);
void turnAbsolute(int degrees, double power);
void curve(int heading, double radiusOfTurn, double power);
double inchesToDegrees(double distanceToMove);
double degreesToInches(double distanceToMove);
void activateIntake(int speed);
void toggleMOGO();
void toggleLift();
void toggleIntakeCount();

#endif  // FUNCTIONS_HPP