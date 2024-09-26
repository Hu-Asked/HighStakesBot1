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

pros::Motor_Group LeftDrive({m1, m2, m3});
pros::Motor_Group RightDrive({m4, m5, m6});

pros::IMU imu(14);

pros::ADIDigitalOut clampPiston('A');
pros::ADIDigitalOut liftPiston('B');
pros::ADIDigitalOut intakeSizePiston('C');

double wheelDiameter = 3.25;
double gearRatio = 36/48;

double updateRelativeHeading(double relativeHeading, double initialImuHeading, double currentImuHeading) {
    relativeHeading = currentImuHeading - initialImuHeading;
    if (relativeHeading > 180) {
        relativeHeading -= 360;
    } else if (relativeHeading < -180) {
        relativeHeading += 360;
    }
    return relativeHeading;
}

double forcedDecelerate(double remainDistance, double driveSpeed, int minSpeed, double startDistance, bool isReverse) {
    if (isReverse) {
        if (remainDistance >= 0) {
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

    return std::clamp(floor(currentSpeed), (double)minSpeed, (double)driveSpeed);
}

double inchesToDegrees(int distanceToMove) {  // Distance to move in inches
    double degreesToMove = (distanceToMove / (wheelDiameter * M_PI)) * 360;
    return degreesToMove / gearRatio;
}
double degreesToInches(int distanceToMove) {  // Distance to move in degrees
    return distanceToMove * gearRatio / 360 * (wheelDiameter * M_PI);
}

void drive(double target, double power, bool decelerateAtEnd) {
    bool isDecelerating = false;
    double initialHeading = imu.get_heading();
    double relativeHeading = 0;
    m1.tare_position();
    double temp = power;
    double LPower;
    double RPower;
    double time = 0;
    double max = power + 27.0;
    target = inchesToDegrees(target);
    while (true) {
        if (decelerateAtEnd) {
            power = forcedDecelerate(degreesToInches(target) - degreesToInches(m1.get_position()), temp, 15, 6.5, target < 0);
        }

        LPower = power;
        RPower = power;
        double turnError = pidH.calculateError(relativeHeading, 0);
        double error = pidD.calculateError(m1.get_position(), target);
        if (pidD.stop) {
            pidD.stop = false;
            pidD.timer = 0;
            pidD.maxTimeTimer = 0;
            break;
        }
        LPower = LPower * error + std::clamp(LPower * turnError, -27.0, 27.0);
        RPower = RPower * error + std::clamp(RPower * -turnError, -27.0, 27.0);
        LeftDrive.move(std::clamp(LPower, -max, max));
        RightDrive.move(std::clamp(RPower, -max, max));
        relativeHeading = updateRelativeHeading(relativeHeading, initialHeading, imu.get_heading());
        pros::delay(10);
    }
    pros::lcd::print(6, "Target: %f", target);
    pros::lcd::print(5, "Position: %f", m1.get_position());
    LeftDrive.move(0);
    RightDrive.move(0);
}
int calculateTurn(int currentHeading, int targetHeading) {
    int difference = targetHeading - currentHeading;

    difference = ((difference + 180) % 360) - 180;

    if (difference < -180) {
        difference += 360;
    }
    return difference * -1;
}

void turnAbsolute(int degrees, double power) {
    degrees = degrees % 360;
    double initialHeading = imu.get_heading();
    double relativeHeading = 0;
    double target = calculateTurn(initialHeading, degrees);
    while (true) {
        master.print(0, 5, "Heading: %f", imu.get_heading());
        double error = pidH.calculateError(relativeHeading, target);
        LeftDrive.move(std::clamp(power * error, -127.0, 127.0));
        RightDrive.move(std::clamp(power * -error, -127.0, 127.0));
        if (pidH.stop) {
            pidH.stop = false;
            pidH.timer = 0;
            pidH.maxTimeTimer = 0;
            break;
        }
        relativeHeading = (relativeHeading, initialHeading, imu.get_heading());
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
}

void toggleLift() {
    liftPiston.set_value(!isLifted);
    isLifted = !isLifted;
}

void toggleIntakeCount() {
    intakeSizePiston.set_value(!isIntakeIncreased);
    isIntakeIncreased = !isIntakeIncreased;
}
