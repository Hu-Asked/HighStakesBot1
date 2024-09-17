#include "functions.hpp"
#include "pid.hpp"

PIDController pidH(0.023, 0.011, 0.144);
PIDController pidD(0.21, 0, 0.03);

pros::Motor m1(1, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m2(2, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m3(3, MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);


pros::Motor m4(4, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m5(5, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor m6(6, MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor_Group LeftDrive({m1,m2,m3});
pros::Motor_Group RightDrive({m4,m5,m6});

pros::IMU imu(14);

pros::ADIDigitalOut clampPiston('A');
pros::ADIDigitalOut liftPiston('B');
pros::ADIDigitalOut intakeSizePiston('C');

double forcedDecelerate(double remainDistance, double driveSpeed, int minSpeed, double startDistance, bool isReverse) {
    if(isReverse) {
		if(remainDistance >= 0) {
			return minSpeed;
		}
	} else {
		if (remainDistance <= 0) {
			return minSpeed;
		}
	}
    double decelerationSlope = (driveSpeed - minSpeed) / startDistance;

    double currentSpeed = driveSpeed - (decelerationSlope * (startDistance - abs(remainDistance)));

    if (currentSpeed < minSpeed) {
        currentSpeed = minSpeed;
    }
    
    return std::clamp(floor(currentSpeed), (double)minSpeed, (double) driveSpeed);
}

double inchesToDegrees(int distanceToMove) { //Distance to move in inches
	double degreesToMove = (distanceToMove / (3.25*M_PI)) * 360;
	return degreesToMove * 48/36;
}
double degreesToInches(int distanceToMove) { //Distance to move in inches
	return distanceToMove * 36/48 / 360 * (3.25*M_PI);
}
double calculateOptimalTurn(int degrees) {
	double error = abs(pidH.calculateError(imu.get_heading(), degrees % 360));
		if(imu.get_heading() < degrees) {
			//Make Right Drive move by -error
			if(abs(imu.get_heading() - degrees) < 180) {
				return error;
			} else {
				return -error;
			}
		} else {
			if(abs(imu.get_heading() - degrees) < 180) {
				return -error;
			} else {
				return error;
			}
		}
}

void drive(double target, double power, bool decelerateAtEnd) {
	bool isDecelerating = false;
	int curHeading = imu.get_heading();
    m1.tare_position();
	double temp = power;
	double LPower = power;
	double RPower = power;
	double time = 0;
	double max = power + 27.0;
    target = inchesToDegrees(target);
	while(true) {
        if(decelerateAtEnd) {
           power = forcedDecelerate(degreesToInches(target) - degreesToInches(m1.get_position()), temp, 15, 6.5, target < 0);
        }

		LPower = power;
		RPower = power;
		double turnError;		
		turnError = calculateOptimalTurn(curHeading);
		double error = pidD.calculateError(m1.get_position(), target);
        if(pidD.stop) {
            pidD.stop = false;
            pidD.timer = 0;
            break;
        }
		LPower = LPower * error + std::clamp(LPower * turnError, -27.0, 27.0);
		RPower = RPower * error + std::clamp(RPower * -turnError, -27.0, 27.0);
		LeftDrive.move(std::clamp(LPower, -max, max));
		RightDrive.move(std::clamp(RPower, -max, max));
        
		pros::delay(10);
	}
    pros::lcd::print(6, "Target: %f", target);
    pros::lcd::print(5, "Position: %f", m1.get_position());
	LeftDrive.move(0);
	RightDrive.move(0);
}

void turn(int degrees, double power) {
	imu.tare_heading();
	degrees = degrees % 360;
	while(true) {
		master.print(0, 5, "Heading: %f", imu.get_heading());
		double error = calculateOptimalTurn(degrees);
		LeftDrive.move(std::clamp(power * error, -127.0, 127.0));
		RightDrive.move(std::clamp(power * -error, -127.0, 127.0));
		if(pidH.stop) {
			pidH.stop = false;
            pidH.timer = 0;
			break;
		}
		pros::delay(10);
	}
	LeftDrive.move(0);
	RightDrive.move(0);
}

void turnAbsolute(int degrees, double power) { //Use either relative or absolute, don't use both in the same routine
	degrees = degrees % 360;
	while(true) {
		master.print(0, 5, "Heading: %f", imu.get_heading());
		double error = calculateOptimalTurn(degrees);
		LeftDrive.move(std::clamp(power * error, -127.0, 127.0));
		RightDrive.move(std::clamp(power * -error, -127.0, 127.0));
		if(pidH.stop) {
			pidH.stop = false;
            pidH.timer = 0;
			break;
		}
		pros::delay(10);
	}
	LeftDrive.move(0);
	RightDrive.move(0);
}
bool isClamped = false;
bool isLifted = false;
bool isExtended = false;
bool isIntakeIncreased = false;

void activateIntake(int speed) {
    intake1.move(speed);
    intake2.move(speed);
}

void toggleClamp() {
    clampPiston.set_value(!isClamped);
    isClamped = !isClamped;
	pros::delay(400)
;}

// void extendIntake() {
// 	intakeExtendPiston.set_value(!isExtended);
// 	isExtended = !isExtended;
// }

void toggleLift() {
    liftPiston.set_value(!isLifted);
    isLifted = !isLifted;
}

void toggleIntakeCount() {
    intakeSizePiston.set_value(!isIntakeIncreased);
    isIntakeIncreased = !isIntakeIncreased;
}
