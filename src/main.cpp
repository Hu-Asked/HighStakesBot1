#include "main.h"

// ez::Drive chassis (
//   // Left Chassis Ports (negative port will reverse it!)
//   //   the first port is used as the sensor
//   {-1,-2,-3}

//   // Right Chassis Ports (negative port will reverse it!)
//   //   the first port is used as the sensor
//   ,{4,5,6}

//   // IMU Port
//   ,14

//   ,3.25

//   // Cartridge RPM
//   ,600

//   ,0.75
// );

// Odometry odometry;
pros::Motor intake1(9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2(10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

// pros::ADIDigitalOut piston1('A');
// pros::ADIDigitalOut piston2('B');
// pros::ADIDigitalOut piston3('C');
// pros::ADIDigitalOut piston4('D');

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
        Auton("Red Left", RedLeft),
        Auton("Red Right \nMOGO rush", RedRight),
        Auton("Red Right 2 \nTwo rings two stakes", RedRight2),
        Auton("Blue Left", BlueLeft),
        Auton("Blue Right \nMOGO rush", BlueRight),
        Auton("Blue Right 2 \nTwo rings two stakes", BlueRight2),
        Auton("Skills", AutonomousSkills),
        Auton("Drive Example\n\nRobot drives forward", drive_example),
        Auton("Turn Example\n\nRobot turns 90 degrees", turn_example),
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
    while (true) {
        master.print(0, 0, "Heading: %f", imu.get_heading());
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

        if (master.get_digital_new_press(DIGITAL_A)) toggleClamp();
        if (master.get_digital_new_press(DIGITAL_Y)) toggleLift();
        if (master.get_digital_new_press(DIGITAL_X)) toggleIntakeCount();

        // if(master.get_digital(DIGITAL_B)) toggleClamp();
        // if(master.get_digital(DIGITAL_A)) toggleLift();
        // if(master.get_digital(DIGITAL_Y)) toggleIntakeCount();

        pros::delay(ez::util::DELAY_TIME);
    }
}
