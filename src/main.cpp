#include "main.h"

void initialize() {
    pros::delay(500);
    LeftDrive.set_brake_modes(MOTOR_BRAKE_HOLD);
    RightDrive.set_brake_modes(MOTOR_BRAKE_HOLD);
    imu.reset();
    while (imu.is_calibrating()) {
        pros::delay(10);
    }
    default_constants();
    ez::as::auton_selector.autons_add({
        Auton("Red Rings", RedRings),
        Auton("Red MOGO \nMOGO rush", RedMOGO),
        Auton("Red MOGO 2 \nTwo rings two stakes", RedMOGO2),
        Auton("Blue Rings", BlueRings),
        Auton("Blue MOGO \nMOGO rush", BlueMOGO),
        Auton("Blue MOGO 2 \nTwo rings two stakes", BlueMOGO2),
        Auton("Skills", AutonomousSkills),
        Auton("Drive Example\n\nRobot drives forward", drive_example),
        Auton("Turn Example\n\nRobot turns 90 degrees", turn_example),
        Auton("Curve Example\n\nRobot curves", curve_example)
    });
    ez::as::initialize();
    master.rumble(".");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    imu.tare_heading();
    ez::as::auton_selector.selected_auton_call();
}

int turningCurve = 10;
bool isTurningCurve = false;
int forwardCurve = 20;
bool isForwardCurve = false;

double curveJoystick(bool isCurve, int input, double t) {
    int val = 0;
    if (isCurve) {
        val = (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
    } else {
        val = std::exp(((std::abs(input) - 100) * t) / 1000) * input;
    }
    return val;
}

void opcontrol() {
    double startTime = pros::millis();
    bool isNotified = false;
    while (true) {
        if (!pros::competition::is_connected()) {
            if (master.get_digital_new_press(DIGITAL_RIGHT))
                autonomous();
        }

        int LeftY = std::clamp(curveJoystick(isForwardCurve, master.get_analog(ANALOG_LEFT_Y), forwardCurve), -100.0, 100.0);
        int RightX = std::clamp(curveJoystick(isTurningCurve, master.get_analog(ANALOG_RIGHT_X), turningCurve), -100.0, 100.0);
        int leftPower = LeftY + RightX;
        int rightPower = LeftY - RightX;
        pros::delay(10);
        LeftDrive.move(leftPower);
        RightDrive.move(rightPower);

        if (master.get_digital(DIGITAL_L1)) {
            activateIntake(110);
        } else if (master.get_digital(DIGITAL_R1)) {
            activateIntake(-110);
        } else {
            activateIntake(0);
        }

        if (master.get_digital_new_press(DIGITAL_A)) toggleMOGO();
        if (master.get_digital_new_press(DIGITAL_Y)) toggleLift();
        if (master.get_digital_new_press(DIGITAL_X)) toggleIntakeCount();

        if(!isNotified && pros::millis() - startTime >= 85000) {
            master.rumble("--------");
            isNotified = true;
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}
