#include "main.h"
#include "pid.hpp"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

extern pros::Motor intake1;
extern pros::Motor intake2;

extern pros::ADIDigitalOut clampPiston1;
extern pros::ADIDigitalOut clampPiston2;
extern pros::ADIDigitalOut liftPiston1;
extern pros::ADIDigitalOut liftPiston2;
extern pros::ADIDigitalOut intakeSpacePiston1;
extern pros::ADIDigitalOut intakeSpacePiston2;

extern PIDController pidH;
extern PIDController pidD;

void drive(double target, double power, bool autoHeading, bool decelerateAtEnd);
double decelerate(double remainDistance, int minSpeed, double startDistance);

void activateIntake(int speed);
void toggleClamp();
void toggleLift();
void toggleIntakeCount();

#endif // FUNCTIONS_HPP