#include "main.h"

// These are out of 127
const int DRIVE_SPEED = 100;
const int TURN_SPEED = 90;

void default_constants() {
    pidD.setExitCondition(1, true, 200, 5000);
}

// Names are according to the field set up on the manual, watch out for mistakes in field orientation
void RedLeft() {
    // align 6 holes with foam tile
    // Robot starts in reverse; rush mogo
    drive(-35, 40, true);
    toggleClamp();

    // activate intake to score preload
    activateIntake(-110);

    turnAbsolute(90, TURN_SPEED);
    drive(17, DRIVE_SPEED, true);
    turnAbsolute(170, TURN_SPEED);
    drive(13, 50, true);
    turnAbsolute(135, TURN_SPEED);
    drive(4, DRIVE_SPEED, true);
    pros::delay(40);

    drive(-20, DRIVE_SPEED, true);
    turnAbsolute(250, TURN_SPEED);
    drive(26, DRIVE_SPEED, true);
}

void RedRight() {
    // drive(-35.5, 40, true);
    // toggleClamp();
    // activateIntake(-110);
    // turnAbsolute(270, TURN_SPEED);
    // drive(16, DRIVE_SPEED, true);
    // turnAbsolute(110, TURN_SPEED);
    // toggleClamp();
    // drive(33, DRIVE_SPEED, true);

    drive(-52, DRIVE_SPEED, true);
    toggleClamp();
    activateIntake(-110);
    drive(15, DRIVE_SPEED, true);
}

void RedRight2() {
    // align preload with intake top c-channel
    // align standoff with tape: standoff on inside of tape
    drive(20, DRIVE_SPEED, true);
    turnAbsolute(93, TURN_SPEED);
    activateIntake(-110);
    drive2(-10, 120, true);
    LeftDrive.move(-127);
    RightDrive.move(-127);
    pros::delay(200);
    LeftDrive.move(0);
    RightDrive.move(0);
    // drive(20, 78, true);
    // turnAbsolute(320, TURN_SPEED);
    // drive(-37, DRIVE_SPEED, true);
    // toggleClamp();
    // turnAbsolute(195, TURN_SPEED);
    // drive(20, DRIVE_SPEED, true);
    // drive(-32, DRIVE_SPEED, true);
    drive(15, 80, true);
    turnAbsolute(180, TURN_SPEED);
    drive(25, DRIVE_SPEED, true);
    turnAbsolute(270, TURN_SPEED);
    drive(-25, 50, true);
    toggleClamp();
    turnAbsolute(190, TURN_SPEED);
    drive(30, DRIVE_SPEED, true);
}

void BlueLeft() {
    // align 6 holes with foam tile
    // Robot starts in reverse; rush mogo
    drive(-35.5, 40, true);
    toggleClamp();

    // activate intake to score preload
    activateIntake(-110);

    turnAbsolute(270, TURN_SPEED);
    drive(16, DRIVE_SPEED, true);
    turnAbsolute(190, TURN_SPEED);
    drive(11, 50, true);
    turnAbsolute(220, TURN_SPEED);
    drive(3.5, DRIVE_SPEED, true);
    pros::delay(40);

    drive(-20, DRIVE_SPEED, true);
    turnAbsolute(90, TURN_SPEED);
    drive(26, DRIVE_SPEED, true);
}

void BlueRight() {
    // start in reverse; rush mogo
    drive(-35.5, 40, true);
    toggleClamp();
    activateIntake(-110);
    turnAbsolute(90, TURN_SPEED);
    drive(16, DRIVE_SPEED, true);
    turnAbsolute(210, TURN_SPEED);
    drive(-30, DRIVE_SPEED, true);
}

void BlueRight2() {
    // align preload with intake top c-channel
    // align standoff with tape: standoff on inside of tape
    drive(18, DRIVE_SPEED, true);
    turnAbsolute(267, TURN_SPEED);
    activateIntake(-110);
    drive2(-7, DRIVE_SPEED, true);
    drive(20, 78, true);
    turnAbsolute(40, TURN_SPEED);
    drive(-37, DRIVE_SPEED, true);
    toggleClamp();
    turnAbsolute(165, TURN_SPEED);
    drive(20, DRIVE_SPEED, true);
    drive(-32, DRIVE_SPEED, true);
}

void AutonomousSkills() {
    // align preload with c-channel

    activateIntake(-110);
    drive2(-7.3, DRIVE_SPEED, true);
    drive(18, DRIVE_SPEED, true);

    turnAbsolute(90, TURN_SPEED);
    drive(-24, 50, true);
    toggleClamp();
    turnAbsolute(1, TURN_SPEED);
    drive(16, DRIVE_SPEED, true);
    turnAbsolute(285, TURN_SPEED);
    drive(28, DRIVE_SPEED, true);
    turnAbsolute(180, TURN_SPEED);
    drive(20, DRIVE_SPEED, true);
    pros::delay(10);
    drive(12, DRIVE_SPEED, true);
    turnAbsolute(307, TURN_SPEED);
    drive(11, DRIVE_SPEED, true);
    turnAbsolute(40, TURN_SPEED);
    drive(-12, 60, true);
    toggleClamp();

    drive(12, DRIVE_SPEED, true);
    turnAbsolute(270, TURN_SPEED);
    drive(-70, DRIVE_SPEED, true);
    toggleClamp();
    drive(-5, DRIVE_SPEED, true);
    turnAbsolute(0, TURN_SPEED);
    drive(15, DRIVE_SPEED, true);
    turnAbsolute(80, TURN_SPEED);
    drive(25, DRIVE_SPEED, true);
    turnAbsolute(180, TURN_SPEED);
    drive(20, DRIVE_SPEED, true);
    drive(12, DRIVE_SPEED, true);

    // Step 5-9 (put rings on neutral stakes)

    // Step 10, get center ring and mogo
    // Get 3 more rings, then drop off in corner
    // 3 rings on neutral stake

    // grab mogo and put in
}
void drive_example() {
    drive(40, DRIVE_SPEED, true);
}

void turn_example() {
    turn(90, TURN_SPEED);
}