#include "main.h"

// These are out of 127
const int DRIVE_SPEED = 80;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 50;

void default_constants() {
  // chassis.pid_heading_constants_set(6.4, 14.1, 43.6);
  // chassis.pid_drive_constants_set(15, 0, 0);
  // chassis.pid_turn_constants_set(6.4, 14.1, 43.6);
  // chassis.pid_swing_constants_set(5, 0, 30);

  // chassis.pid_turn_exit_condition_set(200_ms, 2_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  // chassis.pid_swing_exit_condition_set(200_ms, 2_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  // chassis.pid_drive_exit_condition_set(200_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  // chassis.slew_drive_constants_set(7_in, 50);
}

void RedLeft() {
  //Robot starts in reverse; rush mogo
  drive(-35, 40, true); 
  toggleClamp();

  //activate intake to score preload
  activateIntake(-110);

  turnAbsolute(90, TURN_SPEED);
  drive(17, DRIVE_SPEED, true);
  turnAbsolute(170, TURN_SPEED);
  drive(13, 50, true);
  turnAbsolute(130, TURN_SPEED);
  drive(4.5, DRIVE_SPEED, true);
  pros::delay(40);

  drive(-20, DRIVE_SPEED, true);
  turnAbsolute(250, TURN_SPEED);
  drive(20, DRIVE_SPEED, false);
}

void RedRight() {
  drive(-16, 110, true);
  turnAbsolute(60, TURN_SPEED);
  drive(-32, 110, true);
  turnAbsolute(355, TURN_SPEED);
  drive(-20, DRIVE_SPEED, true);
  toggleClamp();
  drive(20, DRIVE_SPEED, true);
} 

void RedRight2() {
  drive(30, DRIVE_SPEED, true);
  turn(45, TURN_SPEED);
  drive(-20, DRIVE_SPEED, true);
  activateIntake(-110);
  turnAbsolute(90, TURN_SPEED);
  pros::delay(300);
  activateIntake(0);
  drive(12, DRIVE_SPEED, true);
  turnAbsolute(315, TURN_SPEED);
  drive(-40, 60, true);
  toggleClamp();
  turnAbsolute(180, TURN_SPEED);
  drive(30, DRIVE_SPEED, true);
}

void BlueLeft() {
  //Robot starts in reverse; rush mogo
  drive(-36, 40, true); 
  toggleClamp();

  //activate intake to score preload
  activateIntake(-110);

  turnAbsolute(270, TURN_SPEED);
  drive(16, DRIVE_SPEED, true);
  turnAbsolute(190, TURN_SPEED);
  drive(11, 50, true);
  turnAbsolute(220, TURN_SPEED);
  drive(4, DRIVE_SPEED, true);
  pros::delay(40);

  drive(-20, DRIVE_SPEED, true);
  turnAbsolute(90, TURN_SPEED);
  drive(25, DRIVE_SPEED, true);
}

void BlueRight() {
  //start in reverse; rush mogo
  drive(-16, 110, true);
  turnAbsolute(300, TURN_SPEED);
  drive(-32, 110, true);
  turnAbsolute(5, TURN_SPEED);
  drive(-20, DRIVE_SPEED, true);
  toggleClamp();
  drive(20, DRIVE_SPEED, true);
}

void BlueRight2() {
  //go for alliance stake first
  drive(30, DRIVE_SPEED, true);
  turn(315, TURN_SPEED);
  drive(-20, DRIVE_SPEED, true);
  activateIntake(-110);
  turnAbsolute(270, TURN_SPEED);
  pros::delay(300);
  activateIntake(0);
  drive(12, DRIVE_SPEED, true);
  turnAbsolute(45, TURN_SPEED);
  drive(-40, 60, true);
  toggleClamp();
  turnAbsolute(180, TURN_SPEED);
  drive(30, DRIVE_SPEED, true);
}

void AutonomousSkills() {
  //robot starts in reverse; rush mogo
  drive(-10, DRIVE_SPEED, true);
  toggleClamp();
  turn(180, TURN_SPEED);
  activateIntake(-90);
  drive(5, DRIVE_SPEED, true);

  turn(270, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);

  turn(270, TURN_SPEED);
  drive(10, DRIVE_SPEED, true);

  turn(135, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);


  //align with wall
  turn(270, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);

  activateIntake(0);
  turn(270, TURN_SPEED);
  drive(-5, DRIVE_SPEED, true);
  toggleClamp();

  //aim towards next mogo, then drive partway, then turn 180 to line up with clamp
  turn(45, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  turn(180, TURN_SPEED);
  drive(-10, DRIVE_SPEED, true);
  toggleClamp();

  turn(90, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  turn(90, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);

  turn(35, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  turn(35, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  turn(90, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  turn(270, TURN_SPEED);
  drive(5, DRIVE_SPEED, true);
  
  //align with wall, reverse, then drop off mogo

  //Step 5-9 (put rings on neutral stakes)

  //Step 10, get center ring and mogo
  //Get 3 more rings, then drop off in corner
  //3 rings on neutral stake

  //grab mogo and put in

  toggleClamp();  


}
void drive_example() {
  drive(40, DRIVE_SPEED, true);
}


void turn_example() {
  turn(90, TURN_SPEED);
}