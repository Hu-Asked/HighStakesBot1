#include "main.h"
#include "pid.hpp"
#include <cmath>

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

extern pros::Motor m1;
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

double updateRelativeHeading(double initialImuHeading, double currentImuHeading);
void drive(double target, double power, bool decelerateAtEnd);
void drive(double target, double power, bool decelerateAtEnd, std::function<void()> customFunction, double positionToCall);
void turnAbsolute(int degrees, double power);
double inchesToDegrees(double distanceToMove);
double degreesToInches(double distanceToMove);
void activateIntake(int speed);
void toggleMOGO();
void toggleLift();
void toggleIntakeCount();

#endif  // FUNCTIONS_HPP