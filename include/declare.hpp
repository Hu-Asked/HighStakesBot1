#pragma once

#include "main.h"
#include "pid.hpp"

#define PROS_USE_SIMPLE_NAMES

#include "functions.hpp"

extern PIDController pidH;
extern PIDController pidD;

extern pros::Motor m1;
extern pros::Motor m2;
extern pros::Motor m3;

extern pros::Motor m4;
extern pros::Motor m5;
extern pros::Motor m6;

extern pros::Motor_Group LeftDrive;
extern pros::Motor_Group RightDrive;

extern pros::IMU imu;

extern pros::ADIDigitalOut clampPiston;
extern pros::ADIDigitalOut liftPiston;
extern pros::ADIDigitalOut intakeSizePiston;

// Odometry odometry;
extern pros::Motor intake1;
extern pros::Motor intake2;

extern const double wheelDiameter;
extern const double gearRatio ;
extern const double distanceBetweenDrivepods;

extern const int DRIVE_SPEED;
extern const int TURN_SPEED;

void default_constants();