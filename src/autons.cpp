#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 100;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 50;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(6.4, 14.1, 43.6);
  chassis.pid_drive_constants_set(15, 0, 0);
  chassis.pid_turn_constants_set(6.4, 14.1, 43.6);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(200_ms, 2_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(200_ms, 2_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(200_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 50);
}

void setMobileGoalPID() { // Set the PID constants for when carrying the mobile goal
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(3, 3, 3);
}

void RedLeft() {
  // Add your autonomous code here
  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

}

void RedRight() {
  chassis.pid_swing_relative_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_relative_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
  
  chassis.pid_swing_relative_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
  
  chassis.pid_swing_relative_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
}

void BlueLeft() {
  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-20_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();

}

void BlueRight() {
  chassis.pid_swing_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
  chassis.pid_swing_set(RIGHT_SWING, 0_deg, SWING_SPEED);
  chassis.pid_wait();
  chassis.pid_swing_set(RIGHT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
  chassis.pid_swing_set(LEFT_SWING, 0_deg, SWING_SPEED);
}

void AutonomousSkills() {
  // Add your autonomous code here
}
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inche
  drive(40, DRIVE_SPEED, true, true);
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}


void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::lcd::set_text(1, to_string(chassis.imu.get_heading()));
}

void swing_example() {
  chassis.pid_swing_set(LEFT_SWING, 90_deg, SWING_SPEED);
  chassis.pid_wait();
  chassis.pid_swing_set(LEFT_SWING, 0_deg, SWING_SPEED);
  chassis.pid_wait();
}
///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}