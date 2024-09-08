#include "functions.hpp"
#include "pid.hpp"

PIDController pidH(0.1, 0, 0);
PIDController pidD(0.01, 0, 0);

pros::Motor m1(1, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m2(2, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m3(3, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);


pros::Motor m4(4, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m5(5, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m6(6, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor_Group LeftDrive({m1,m2,m3});
pros::Motor_Group RightDrive({m4,m5,m6});

double forcedDecelerate(double remainDistance, int minSpeed, double startDistance) {
    if (remainDistance <= 0) {
        return minSpeed;
    }

    double decelerationSlope = (DRIVE_SPEED - minSpeed) / startDistance;

    double currentSpeed = DRIVE_SPEED - decelerationSlope * (startDistance - remainDistance);

    if (currentSpeed < minSpeed) {
        currentSpeed = minSpeed;
    }

    return currentSpeed;
}

double inchesToDegrees(int distanceToMove) { //Distance to move in inches
	double degreesToMove = (distanceToMove / (3.25*M_PI)) * 360;
	return degreesToMove * 48/36;
}
double dgreesToInches(int distanceToMove) { //Distance to move in inches
	return distanceToMove * 36/48 / 360 * (3.25*M_PI);
}

void drive(double target, double power, bool autoHeading, bool decelerateAtEnd) {
	bool isDecelerating = false;
	int curHeading = chassis.imu.get_heading();
    m1.tare_position();
	double LPower = power;
	double RPower = power;
	double time = 0;
    target = inchesToDegrees(target);
	while(true) {
        master.print(0, 0, "Position: %f", m1.get_position());
        // if(decelerateAtEnd) {
        //     power = forcedDecelerate(target - dgreesToInches(m1.get_position()), 30, 10);
        // }
		LPower = power;
		RPower = power;
		double turnError;		
		turnError = pidH.calculateError(chassis.imu.get_heading(), curHeading);
		double error = pidD.calculateError(m1.get_position(), target);
        if(pidD.stop) {
            pidD.stop = false;
            break;
        }
		LeftDrive.move(LPower * error);
		RightDrive.move(RPower * error);
		// RightDrive.move(clamp(RPower * error + RPower * -turnError, -127.0, 127.0));
		pros::delay(10);
	}
	LeftDrive.move(0);
	RightDrive.move(0);
}

bool isClamped = false;
bool isLifted = false;
bool isIntakeIncreased = false;

void activateIntake(int speed) {
    intake1.move(speed);
    intake2.move(speed);
}

void toggleClamp() {
    clampPiston1.set_value(!isClamped);
    clampPiston2.set_value(!isClamped);
    isClamped = !isClamped;
}

void toggleLift() {
    liftPiston1.set_value(!isLifted);
    liftPiston2.set_value(!isLifted);
    isLifted = !isLifted;
}

void toggleIntakeCount() {
    intakeSpacePiston1.set_value(!isIntakeIncreased);
    intakeSpacePiston2.set_value(!isIntakeIncreased);
    isIntakeIncreased = !isIntakeIncreased;
}
