#include "functions.hpp"

PIDController pidH(0.023, 0.011, 0.144);
PIDController pidD(0.21, 0, 0.03);

pros::Motor m1(1, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m2(2, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m3(3, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor m4(4, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m5(5, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m6(6, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor_Group LeftDrive({m1, m2, m3});
pros::Motor_Group RightDrive({m4, m5, m6});

pros::IMU imu(14);

pros::ADIDigitalOut clampPiston('A');
pros::ADIDigitalOut liftPiston('B');
pros::ADIDigitalOut intakeSizePiston('C');

// Odometry odometry;
pros::Motor intake1(9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2(10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

const double wheelDiameter = 3.25;
const double gearRatio = 36.0/48.0;
const double distanceBetweenDrivepods = 12;

const int DRIVE_SPEED = 100;
const int TURN_SPEED = 90;

void default_constants() {
    pidD.setExitCondition(inchesToDegrees(1), 200, 5000);
    pidH.setExitCondition(2, 200, 3000);
}