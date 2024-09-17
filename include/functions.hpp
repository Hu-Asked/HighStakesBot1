#include "main.h"
#include "pid.hpp"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

extern pros::Motor intake1;
extern pros::Motor intake2;

extern pros::Motor_Group LeftDrive;
extern pros::Motor_Group RightDrive;
extern pros::IMU imu;

extern pros::ADIDigitalOut clampPiston;
extern pros::ADIDigitalOut liftPiston1;
extern pros::ADIDigitalOut liftPiston2;
extern pros::ADIDigitalOut intakeSpacePiston1;
extern pros::ADIDigitalOut intakeSpacePiston2;

extern PIDController pidH;
extern PIDController pidD;

void drive(double target, double power, bool decelerateAtEnd);
void turn(int degrees, double power);
void turnAbsolute(int degrees, double power);
double inchesToDegrees(int distanceToMove);
double degreesToInches(int distanceToMove);

void activateIntake(int speed);
void toggleClamp();
void toggleLift();
void extendIntake();
void toggleIntakeCount();

#endif // FUNCTIONS_HPP